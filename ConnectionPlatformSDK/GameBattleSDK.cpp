#include "GameBattleSDK.h"
#include "inc/MathHelper.h"

#include "inc/TimeHelper.h"

#include <sstream>
#include <iostream>

using namespace std::chrono;

GameBattleSDK::GameBattleSDK()
{
    m_pNetCon = new NetConnector();
    m_pNetCon->Init();
    m_ip = "192.168.1.233";
}

GameBattleSDK::~GameBattleSDK()
{
    SAFE_DELETE_PTR(m_pNetCon);
}

Json::Value GameBattleSDK::GenerateHeadMessage(int bID, int action, int encrypt)
{
    Json::Value JsonRoot;
    JsonRoot["bId"] = Json::Value(bID);
    JsonRoot["action"] = Json::Value(action);

    string sessionid = m_pNetCon->GetHeadData()->sessionid;
    __LogInfo(L"se ID is %s", sessionid);
    
    JsonRoot["sessionid"] = Json::Value(sessionid);

    m_llCurSerial = GetSerialNumber();
    JsonRoot["serialNumber"] = Json::Value(m_llCurSerial);


    JsonRoot["encrypt"] = Json::Value(encrypt);

    return JsonRoot;
}

long long GameBattleSDK::GetSerialNumber()
{
    long long serialNum;

    time_t t;
    time(&t);
    serialNum = t * 1000000;

    srand(t);
    int ranNum = GenerateRanNum();
    serialNum += ranNum;
    return serialNum;
}

void GameBattleSDK::ConnectPlatform(std::string cpId, std::string gameId, std::string userName, std::string userNick)
{
    m_pNetCon->StartConnecting(0, m_ip.c_str(), 9012);
    Json::Value JsonRoot;
    JsonRoot["cpId"] = Json::Value(cpId);
    JsonRoot["gameId"] = Json::Value(gameId);
    JsonRoot["userName"] = Json::Value(userName);
    JsonRoot["userNick"] = Json::Value(userNick);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 1, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->ConData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::GetGameRoomList(string cpId, string gameId)
{
    //m_pNetCon->StartConnecting(5058, m_ip.c_str(), 9012);
    Json::Value JsonRoot;

    JsonRoot["cpId"] = Json::Value(cpId);
    JsonRoot["gameId"] = Json::Value(gameId);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 2, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->RLData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::CreateGameRoom(string cpId, string gameId, string& roomName, int maxMembers, string& custom)
{
    //m_pNetCon->StartConnecting(5058, m_ip.c_str(), 9012);
    Json::Value JsonRoot;

    JsonRoot["cpId"] = Json::Value(cpId);
    JsonRoot["gameId"] = Json::Value(gameId);
    JsonRoot["roomName"] = Json::Value(roomName);
    JsonRoot["maxMembers"] = Json::Value(maxMembers);
    JsonRoot["custom"] = Json::Value(custom);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 3, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->CRData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::JoinGameRoom(string& roomId)
{
    Json::Value JsonRoot;

    JsonRoot["roomId"] = Json::Value(roomId);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 5, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->JRData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::RefreshRoomInfo(string& roomId, string& custom)
{
    Json::Value JsonRoot;

    JsonRoot["roomId"] = Json::Value(roomId);
    JsonRoot["custom"] = Json::Value(custom);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 4, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->RRData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::GetGameRoomUserList(string& roomId)
{
    Json::Value JsonRoot;

    JsonRoot["roomId"] = Json::Value(roomId);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 6, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->ULData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::ModifyUserStatus(string& custom)
{
    Json::Value JsonRoot;

    JsonRoot["custom"] = Json::Value(custom);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 7, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->MGData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::QuitGameRoom(string roomId)
{
    Json::Value JsonRoot;

    JsonRoot["roomId"] = Json::Value(roomId);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 8, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->QGData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::RefreshRoomStatus(string& roomId, int status)
{
    Json::Value JsonRoot;

    JsonRoot["roomId"] = Json::Value(roomId);
    JsonRoot["status"] = Json::Value(status);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 9, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->RRSData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::DisconnectPlatform()
{
    Json::Value JsonRoot;

    JsonRoot = GenerateHeadMessage(1, 10, 0);
    JsonRoot["data"] = Json::Value("");
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->DisData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::ConnectHeartBeats()
{
    Json::Value JsonRoot;
    JsonRoot = GenerateHeadMessage(2, 11, 0);
    JsonRoot["data"] = Json::Value("");
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::TransmitUserMessage(string& roomId, string& custom)
{
    Json::Value JsonRoot;

    JsonRoot["roomId"] = Json::Value(roomId);
    JsonRoot["custom"] = Json::Value(custom);
    string data = JsonRoot.toStyledString();

    JsonRoot = GenerateHeadMessage(1, 2, 0);
    JsonRoot["data"] = Json::Value(data);
    string message;
    message = JsonRoot.toStyledString();

    m_pNetCon->RLData()->m_llSendSerial = m_llCurSerial;

    m_pNetCon->SendData(message.c_str(), message.size());
}

void GameBattleSDK::SetConnectIp(string val)
{
    m_ip = val;
}

