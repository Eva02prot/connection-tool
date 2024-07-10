#pragma once

//#define testServer
#include <winsock2.h>
typedef SOCKET socket_t;

#include "../inc/TimeHelper.h"
#include "../inc/StringHelper.h"
#include "../inc/KernelHelper.h"
#include "NetTypes.h"
#include "../GameData.h"
#include "../inc/LogManager.h"

class NetConnector : SyncObject
{
public:
    ~NetConnector();


    //static NetConnector * GetInstance()
    //{
    //    static NetConnector instance;
    //    return &instance;
    //}

    bool        Init();
    void        Reset();

    void        CloseConnection();
    void        CloseConnectionInternal();

    bool        StartConnecting(int localPort, const char* hostName, int hostPort);
    bool        StartListening(int localPort);
    void        StartDisconnecting();

    bool        CreateSocket(int localPort);

    bool        SendData(const std::string data, size_t dataSize);
    int         ReceiveData(uint8_t* buf, size_t bufSize);

    void        HandleHeadMes(uint8_t* buff, const int size);
    void        HandleBodyMes(std::string &mess);

    void        Run();

    void        EnterConnectedStatus();

    HeadData*   GetHeadData() {return &_curHead;}

    ConnectData* ConData() const { return m_pConData; }
    RoomListData* RLData() const { return m_pRLData; }
    CreateRoomData* CRData() const { return m_pCRData; }
    RefreshRoomData* RRData() const { return m_pRRData; }
    JoinRoomData* JRData() const { return m_pJRData; }
    UserListData* ULData() const { return m_pULData; }
    ModifyGameData* MGData() const { return m_pMGData; }
    QuitGameData* QGData() const { return m_pQGData; }
    RefreshRoomListData* RRSData() const { return m_pRRSData; }
    DisconnectData* DisData() const { return m_pDisData; }
    TransmitData* TSData() const { return m_pTSData; }
private:
    //NetConnector();


    NetConnectorStatus _status = NetConnectorStatus::Disconnected;
    bool _threadRunning = false;

    socket_t _socketFd = 0;
    int _localPort = 0;
    std::wstring _hostName;
    in_addr _hostAddr = {};
    int _hostPort = 0;
    timestamp_t _lastReceivedTime;
    timestamp_t _lastSentTime;
    int _resendDisconnectTimes = 0;

    HeadData _curHead;

    ConnectData*            m_pConData;
    RoomListData*           m_pRLData;
    CreateRoomData*         m_pCRData;
    RefreshRoomData*        m_pRRData;
    JoinRoomData*           m_pJRData;
    UserListData*           m_pULData;
    TransmitData*           m_pTSData;
    ModifyGameData*         m_pMGData;
    QuitGameData*           m_pQGData;
    RefreshRoomListData*    m_pRRSData;
    DisconnectData*         m_pDisData;
};
