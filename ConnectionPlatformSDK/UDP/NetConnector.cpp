#include <ws2tcpip.h>

#define __IsSocketInvalid(socketFd) (socketFd == INVALID_SOCKET)
#define __SocketError() WSAGetLastError()
#define __LastSocketErrorDesc() GetErrorDesc(WSAGetLastError()).c_str()
#define __SocketErrorDesc(err) GetErrorDesc(err).c_str()
#define __ErrorTimedout WSAETIMEDOUT
#define __ErrorWouldBlock WSAEWOULDBLOCK
#define __ErrorIntr WSAEINTR

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <algorithm>
#include "NetConnector.h"
#include "../GameData.h"

static const int netCmd_Heartbeat     = 0;
static const int netCmd_Connect       = 1;
static const int netCmd_Disconnect    = 2;

NetConnector::~NetConnector()
{
    Reset();
    SAFE_DELETE_PTR(m_pConData);
    SAFE_DELETE_PTR(m_pRLData);
    SAFE_DELETE_PTR(m_pCRData);
    SAFE_DELETE_PTR(m_pRRData);
    SAFE_DELETE_PTR(m_pJRData);
    SAFE_DELETE_PTR(m_pULData);
    SAFE_DELETE_PTR(m_pTSData);
    SAFE_DELETE_PTR(m_pMGData);
    SAFE_DELETE_PTR(m_pQGData);
    SAFE_DELETE_PTR(m_pRRSData);
    SAFE_DELETE_PTR(m_pDisData);
}

bool NetConnector::Init()
{
    m_pConData = new ConnectData();
    m_pRLData = new RoomListData();
    m_pCRData = new CreateRoomData();
    m_pRRData = new RefreshRoomData();
    m_pJRData = new JoinRoomData();
    m_pULData = new UserListData();
    m_pTSData = new TransmitData();
    m_pMGData = new ModifyGameData();
    m_pQGData = new QuitGameData;
    m_pRRSData = new RefreshRoomListData();
    m_pDisData = new DisconnectData();

    _curHead.action = -1;
    _curHead.bId = -1;
    _curHead.encrypt = -1;
    _curHead.sessionid = "default";
    _curHead.serialNumber = -1;

    auto lock = AutoLock();

    WSADATA wsad;
    if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0)
    {
        __LogError(L"Socket库初始化失败");
        return false;
    }

    _threadRunning = true;

    std::thread t([=]()
    {
        Run();
    });
    t.detach();

    return true;
}

void NetConnector::Reset()
{
    auto lock = AutoLock();
    CloseConnectionInternal();
    _threadRunning = false;
}

void NetConnector::CloseConnection()
{
    auto lock = AutoLock();
    CloseConnectionInternal();
}

void NetConnector::CloseConnectionInternal()
{
    if (_socketFd != 0)
    {
        closesocket(_socketFd);
        _socketFd = 0;
    }

    _localPort = 0;
    _hostName.clear();
    _hostAddr = {};
    _hostPort = 0;
    _lastReceivedTime = __timestampZero;
    _lastSentTime = __timestampZero;
    _resendDisconnectTimes = 0;
    _status = NetConnectorStatus::Disconnected;
}

bool NetConnector::StartConnecting(int localPort, const char* hostName, int hostPort)
{
    auto lock = AutoLock();

    std::wstring hostNameW = Utf8ToUnicode(hostName);
    __LogInfo(L"开始从本地端口 %d 连接至远程主机 %ls:%d。", localPort, hostNameW.c_str(), hostPort);

    if (_status == NetConnectorStatus::Connected || _status == NetConnectorStatus::Disconnecting)
    {
        __LogError(L"当前网络正处于连接状态，连接失败。");
        return false;
    }
    else if (_status == NetConnectorStatus::Connecting || _status == NetConnectorStatus::Listening)
    {
        CloseConnectionInternal();
    }

    addrinfo* resultInfo = nullptr;
    addrinfo hintsInfo = {};
    hintsInfo.ai_family = AF_INET;
    hintsInfo.ai_socktype = SOCK_DGRAM;
    hintsInfo.ai_protocol = IPPROTO_UDP;

    int err = getaddrinfo(hostName, nullptr, &hintsInfo, &resultInfo);
    if (err != 0)
    {
        __LogError(L"解析域名 %ls 出错: %d。", hostNameW.c_str(), err);
        return false;
    }

    in_addr hostAddr = ((sockaddr_in*)resultInfo->ai_addr)->sin_addr;
    freeaddrinfo(resultInfo);

    if (!CreateSocket(localPort))
    {
        return false;
    }

    _localPort = localPort;
    _hostName = hostNameW;
    _hostAddr = hostAddr;
    _hostPort = hostPort;
    _status = NetConnectorStatus::Connecting;
    return true;
}

bool NetConnector::StartListening(int localPort)
{
    auto lock = AutoLock();

    __LogInfo(L"开始侦听本地端口 %d。", localPort);

    if (_status == NetConnectorStatus::Connected || _status == NetConnectorStatus::Disconnecting)
    {
        __LogError(L"当前网络正处于连接状态，侦听失败。");
        return false;
    }
    else if (_status == NetConnectorStatus::Connecting || _status == NetConnectorStatus::Listening)
    {
        CloseConnectionInternal();
    }

    if (!CreateSocket(localPort))
    {
        return false;
    }

    _localPort = localPort;
    _status = NetConnectorStatus::Listening;
    return true;
}

void NetConnector::StartDisconnecting()
{
    auto lock = AutoLock();

    __LogInfo(L"开始断开连接。");

    if (_status == NetConnectorStatus::Connected)
    {
        _status = NetConnectorStatus::Disconnecting;
    }
    else if (_status == NetConnectorStatus::Connecting || _status == NetConnectorStatus::Listening)
    {
        CloseConnectionInternal();
        __LogInfo(L"连接正常断开。");
    }
    else if (_status == NetConnectorStatus::Disconnected || _status == NetConnectorStatus::Disconnecting)
    {
        __LogInfo(L"连接已经断开或正在断开中，命令无效。");
    }
}

bool NetConnector::CreateSocket(int localPort)
{
    socket_t socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (__IsSocketInvalid(socketFd))
    {
        __LogError(L"创建Socket出错");
        return false;
    }
    _socketFd = socketFd;

    sockaddr_in sockAddr = {};
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port = htons(localPort);

    if (bind(_socketFd, (sockaddr*)&sockAddr, sizeof(sockAddr)) < 0)
    {
        __LogError(L"Socket bind() 出错");
        CloseConnectionInternal();
        return false;
    }
    _localPort = localPort;

    int sockBufSize = 16 * 1024;
    setsockopt(_socketFd, SOL_SOCKET, SO_RCVBUF, (char*)&sockBufSize, sizeof(sockBufSize)); 
    setsockopt(_socketFd, SOL_SOCKET, SO_SNDBUF, (char*)&sockBufSize, sizeof(sockBufSize));

    uint32_t timeout = 10;

    setsockopt(_socketFd, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
    setsockopt(_socketFd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

    return true;
}

bool NetConnector::SendData(const std::string data, size_t dataSize)
{
    sockaddr_in hostSockAddr = {};
    hostSockAddr.sin_family = AF_INET;
    hostSockAddr.sin_addr = _hostAddr;
    hostSockAddr.sin_port = htons(_hostPort);

    char* sendBuf[4096];

    size_t sendSize = (std::min)(dataSize, sizeof(sendBuf));
    memcpy(sendBuf, data.c_str(), sendSize);

    int sizeSent = sendto(_socketFd, (const char*)sendBuf, (int)sendSize, 0,
    (sockaddr*)&hostSockAddr, sizeof(hostSockAddr));
    int err = __SocketError();

    if (sizeSent < 0)
    {
        if (err != __ErrorTimedout && err != __ErrorWouldBlock && err != __ErrorIntr)
        {
            __LogError(L"Socket snedto() 出错");
            CloseConnectionInternal();
            return false;
        }
        return false;
    }

    _lastSentTime = CurTimestamp();
    return true;
}

int NetConnector::ReceiveData(uint8_t* buf, size_t bufSize)
{
    socket_t socketFd = _socketFd;
    sockaddr_in hostSockAddr = {};
    int sockAddrLen = sizeof(hostSockAddr);

    Unlock();
    int sizeReceived = recvfrom(socketFd, (char*)buf, (int)bufSize, 0,
        (sockaddr*)&hostSockAddr, &sockAddrLen);
    int err = __SocketError();
    __LogError("error is %i", err);
    Lock();

    if (!_threadRunning)
    {
        return 0;
    }

    if (sizeReceived < 0)
    {
        if (err != __ErrorTimedout && err != __ErrorWouldBlock && err != __ErrorIntr)
        {
            __LogError(L"Socket recvfrom() 出错: ");
            CloseConnectionInternal();
            return -1;
        }
        else
        {
            return 0;
        }
    }

    if (_status == NetConnectorStatus::Listening)
    {
        _hostAddr = hostSockAddr.sin_addr;
        _hostPort = ntohs(hostSockAddr.sin_port);
    }
    else if (_hostAddr.s_addr != hostSockAddr.sin_addr.s_addr ||
             _hostPort != ntohs(hostSockAddr.sin_port))
    {
        return 0;
    }

    _lastReceivedTime = CurTimestamp();
    return sizeReceived;
}

void NetConnector::HandleHeadMes(uint8_t* buff, const int size)
{
    int totalSize = 60;
    if (size < totalSize)
    {
        __LogError(L"Reviced _curHead size error");
    }

    char temp[32];
    ConvertUint8ToChar(temp, buff, 32);
    _curHead.sessionid = std::string(temp, temp + 32);

    buff += 32;

    _curHead.serialNumber = ConvertUint8ToLongLong(buff, 16);
    buff += 16;

    _curHead.bId = ConvertUint8ToInt(buff, 4);
    buff += 4;

    _curHead.action = ConvertUint8ToInt(buff, 4);
    buff += 4;

    _curHead.encrypt = ConvertUint8ToInt(buff, 4);
    buff += 4;

    int jasSize = size - 60;

    char* jasChar = new char[jasSize];
    memcpy(jasChar, buff, jasSize);
    std::string result = jasChar;
    delete[] jasChar;

    HandleBodyMes(result);
}

void NetConnector::HandleBodyMes(std::string &mess)
{
    switch(_curHead.action)
    {
        case 1:
            m_pConData->HandleMessage(_curHead, mess);
            break;
        case 2:
            m_pRLData->HandleMessage(_curHead, mess);
            break;
        case 3:
            m_pCRData->HandleMessage(_curHead, mess);
            break;
        case 4:
            m_pRRData->HandleMessage(_curHead, mess);
            break;
        case 5:
            m_pJRData->HandleMessage(_curHead, mess);
            break;
        case 6:
            m_pULData->HandleMessage(_curHead, mess);
            break;
        case 7:
            m_pMGData->HandleMessage(_curHead, mess);
            break;
        case 8:
            m_pQGData->HandleMessage(_curHead, mess);
            break;
        case 9:
            m_pRRSData->HandleMessage(_curHead, mess);
            break;
        case 10:
            m_pDisData->HandleMessage(_curHead, mess);
            break;
        case 12:
            TSData()->HandleMessage(_curHead, mess);
            break;
        default:
            __LogError(L"Read Parse error");
    }
}

void NetConnector::Run()
{
    Lock();

    uint8_t receiveBuf[128 * 1024];

    while (_threadRunning)
    {
        if (_status == NetConnectorStatus::Disconnected)
        {
            Unlock();
            SleepInMilliseconds(10);
            Lock();
            continue;
        }

        int receivedSize = ReceiveData(receiveBuf, sizeof(receiveBuf));
        if (receivedSize > 0)
        {
            Unlock();
            EnterConnectedStatus();

#ifdef testServer
            char* p = new char[receivedSize];
            memcpy(p, receiveBuf, receivedSize);
            std::string test = p;
            std::cout << test.c_str() << std::endl;
            delete[] p;
#else // testServer
            HandleHeadMes(receiveBuf, receivedSize);
#endif
            Lock();

            if (!_threadRunning)
            {
                break;
            }
        }
         
        if (_status == NetConnectorStatus::Connected || _status == NetConnectorStatus::Disconnecting)
        {
            if (GetElapsedTime(_lastReceivedTime) >= 30)
            {
                __LogInfo(L"收不到数据包，连接断开。");
                CloseConnectionInternal();
                continue;
            }
        }
    }

        //if (_status == NetConnectorStatus::Connected)
        //{
        //    if (GetElapsedTime(_lastSentTime) >= 0.05)
        //    {
        //        SendData(nullptr, 0, 0xf, netCmd_Heartbeat);
        //    }
        //}
    //    else if (_status == NetConnectorStatus::Connecting)
    //    {
    //        if (GetElapsedTime(_lastSentTime) >= 0.05)
    //        {
    //            SendData(nullptr, 0, 0xf, netCmd_Connect);
    //        }
    //    }
    //    else if (_status == NetConnectorStatus::Disconnecting)
    //    {
    //        if (_resendDisconnectTimes < 3)
    //        {
    //            if (GetElapsedTime(_lastSentTime) >= 0.05)
    //            {
    //                _resendDisconnectTimes++;
    //                SendData(nullptr, 0, 0xf, netCmd_Disconnect);
    //            }
    //        }
    //        else
    //        {
    //            __LogInfo(L"连接正常断开。");
    //            CloseConnectionInternal();
    //            continue;
    //        }
    //    }
    //}

    Unlock();
}

void NetConnector::EnterConnectedStatus()
{
    _status = NetConnectorStatus::Connected;
}

//NetConnector::NetConnector()
//{
//
//}
