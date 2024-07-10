#pragma once

#include "UDP/NetConnector.h"
#include "JaCpp/json.h"

using namespace std;
class GameBattleSDK
{
public:

    static GameBattleSDK * GetInstance()
    {
        static GameBattleSDK instance;
        return &instance;
    }
    virtual ~GameBattleSDK();

    //send message Api
    void            ConnectPlatform(std::string cpid, std::string gameid, std::string username, std::string userNick);
    void            GetGameRoomList(string cpId, string gameId);
    void            CreateGameRoom(string cpId, string gameId, string& roomName, int maxMembers, string& custom);
    void            JoinGameRoom(string& roomId);
    void            RefreshRoomInfo(string& roomId, string& custom);
    void            GetGameRoomUserList(string& roomId);
    void            ModifyUserStatus(string& custom);
    void            QuitGameRoom(string roomId);
    void            RefreshRoomStatus(string& roomId, int status);
    void            DisconnectPlatform();
    void            ConnectHeartBeats();
    void            TransmitUserMessage(string& roomId, string& custom);
    void            SetConnectIp(string val);

    NetConnector*   GetNetControllor() { return m_pNetCon; }

private:
    Json::Value     GenerateHeadMessage(int bID, int action, int encrypt);
    long long       GetSerialNumber();

private:
    GameBattleSDK();
    NetConnector*   m_pNetCon;
    long long       m_llCurSerial;
    string     m_ip;
    //string sessionID = "";
};


