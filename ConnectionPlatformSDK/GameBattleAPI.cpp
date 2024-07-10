#include "GameBattleAPI.h"
#include "GameBattleSDK.h"

//GameBattleSDK* GameBattleSDK::GetInstance() = nullptr;

void LetinvrSDK::ConnectPlatform(std::string cpId, std::string gameId, std::string userName, std::string userNick)
{
    //GameBattleSDK::GetInstance() = new GameBattleSDK();
    if(GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->ConnectPlatform(cpId, gameId, userName, userNick);
}

void LetinvrSDK::GetGameRoomList(std::string cpId, std::string gameId)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->GetGameRoomList(cpId, gameId);
}

void LetinvrSDK::CreateGameRoom(std::string cpId, std::string gameId, std::string roomName, int maxMembers, std::string custom)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->CreateGameRoom(cpId, gameId, roomName, maxMembers, custom);
}

void LetinvrSDK::JoinGameRoom(std::string roomId)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->JoinGameRoom(roomId);
}

void LetinvrSDK::RefreshRoomInfo(std::string roomId, std::string custom)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->RefreshRoomInfo(roomId, custom);
}

void LetinvrSDK::GetGameRoomUserList(std::string roomId)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->GetGameRoomUserList(roomId);
}

void LetinvrSDK::TransmitMessage(std::string roomId, std::string custom)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->TransmitUserMessage(roomId, custom);
}

void LetinvrSDK::ModifyUserStatus(std::string custom)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->ModifyUserStatus(custom);
}

void LetinvrSDK::QuitGameRoom(std::string roomId)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->QuitGameRoom(roomId);
}

void LetinvrSDK::RefreshRoomStatus(std::string roomId, int status)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->RefreshRoomStatus(roomId, status);
}

void LetinvrSDK::DisconnectPlatform()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->DisconnectPlatform();

    //delete GameBattleSDK::GetInstance();
    //GameBattleSDK::GetInstance() = nullptr;
}

void LetinvrSDK::CloseConnectWithServer()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->GetNetControllor()->CloseConnection();
}

void LetinvrSDK::ConnectHeartBeats()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->ConnectHeartBeats();
}

void LetinvrSDK::SetConnectIp(std::string ip)
{
    if (GameBattleSDK::GetInstance() != nullptr)
        GameBattleSDK::GetInstance()->SetConnectIp(ip);
}

const ConnectData* LetinvrSDK::GetConnectData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->ConData();
    return nullptr;
}

const RoomListData* LetinvrSDK::GetRoomListData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->RLData();
    return nullptr;
}

const CreateRoomData* LetinvrSDK::GetCreateRoomData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->CRData();
    return nullptr;
}

const RefreshRoomData* LetinvrSDK::GetRefreshRoomData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->RRData();
    return nullptr;
}

const JoinRoomData* LetinvrSDK::GetJoinRoomData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->JRData();
    return nullptr;
}

const UserListData* LetinvrSDK::GetUserListData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->ULData();
    return nullptr;
}

const TransmitData* LetinvrSDK::GetTransmitData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->TSData();
    return nullptr;
}

const ModifyGameData* LetinvrSDK::GetModifyGameData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->MGData();
    return nullptr;
}

const QuitGameData* LetinvrSDK::GetQuitGameData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->QGData();
    return nullptr;
}

const RefreshRoomListData* LetinvrSDK::GetRefreshRoomStatuData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
        return GameBattleSDK::GetInstance()->GetNetControllor()->RRSData();
    return nullptr;
}

const DisconnectData* LetinvrSDK::GetDisconnectData()
{
    if (GameBattleSDK::GetInstance() != nullptr)
    {
        return GameBattleSDK::GetInstance()->GetNetControllor()->DisData();
    }
    return nullptr;
}
