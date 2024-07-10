#pragma once
#include <string>
#include <vector>

struct HeadData
{
    int bId = -1;
    int action = -1;
    std::string sessionid;
    long long serialNumber = -1;
    int encrypt = 0;
};

class GameDataBase
{
public:
    //GameDataBase();
    //virtual ~GameDataBase();
    virtual void HandleMessage(HeadData &headMes, std::string mes);
    virtual void HandleData(std::string mes) {}
    virtual void SetSerialNumber(long long val) { m_llSendSerial = val; }

    HeadData m_sHeadMes;
    long long m_llSendSerial = -1;
    std::string code = "default";
    std::string message = "default";
    std::string data = "default";
};

class ConnectData : public GameDataBase
{
public:
    void HandleData(std::string mes) override;

    std::string sessionid = "default";
    std::string userNick = "default";
    std::string ip = "default";
    std::string userId = "default";
    int port = -1;
};

class RoomListData : public GameDataBase
{
public:
    ~RoomListData();
    void HandleData(std::string mes) override;

    struct RoomInfo
    {
        std::string roomId = "default";
        std::string roomName = "default";
        int maxNumbers = -1;
        int currentNumbers = -1;
        int status = -1;
        std::string custom = "default";
    };
    std::vector<RoomInfo> m_vRoomInfo;
};

class CreateRoomData : public GameDataBase
{
public:
    void HandleData(std::string mes) override;

    std::string roomId = "default";
    std::string roomName = "default";
};

class RefreshRoomData : public GameDataBase
{

};

class JoinRoomData : public GameDataBase
{
public:
    ~JoinRoomData();
    void HandleData(std::string mes) override;

    struct PlayerInfo
    {
        std::string sessionid = "default";
        std::string userNick = "default";
        std::string ip = "default";
        int port = -1;
        int isMaster = -1;
        std::string custom = "default";
    };
    std::vector<PlayerInfo> m_vPlayerInfo;
};

class UserListData : public GameDataBase
{
public:
    ~UserListData();
    void HandleData(std::string mes) override;

    struct PlayerInfo
    {
        std::string sessionid = "default";
        std::string userNick = "default";
        std::string ip = "default";
        int port = -1;
        int isMaster = -1;
        std::string custom = "default";
    };
    std::vector<PlayerInfo> m_vPlayerInfo;

};

class TransmitData : public GameDataBase
{
public:
    void HandleData(std::string mes) override;

    std::string sessionid = "default";
    std::string sendUserNick = "default";
    std::string custom = "default";
};

class ModifyGameData : public GameDataBase
{
public:
    void HandleData(std::string mes) override {}
};

class QuitGameData : public GameDataBase
{
public:
    void HandleData(std::string mes) override {}
};

class RefreshRoomListData : public GameDataBase
{
public:
    void HandleData(std::string mes) override {}
};

class DisconnectData : public GameDataBase
{
public:
    void HandleData(std::string mes) override {}
};

class HeartBeatData : public GameDataBase
{
public:
    void HandleData(std::string mes) override {}
};