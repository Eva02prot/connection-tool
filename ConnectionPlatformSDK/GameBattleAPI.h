#pragma once

#include <iostream>
#include <stdio.h>
#include "GameData.h"

namespace LetinvrSDK
{
#ifdef __cplusplus

    extern "C++"
    {
#endif	

        void        ConnectPlatform(std::string cpId, std::string gameId, std::string userName, std::string userNick);
        void        GetGameRoomList(std::string cpId, std::string gameId);
        void        CreateGameRoom(std::string cpId, std::string gameId, std::string roomName, int maxMembers, std::string custom = "");
        void        JoinGameRoom(std::string roomId);
        void        RefreshRoomInfo(std::string roomId, std::string custom = "");
        void        GetGameRoomUserList(std::string roomId);
        void        TransmitMessage(std::string roomId, std::string custom);
        void        ModifyUserStatus(std::string custom = "");
        void        QuitGameRoom(std::string roomId);
        void        RefreshRoomStatus(std::string roomId, int status);
        void        DisconnectPlatform();
        void        CloseConnectWithServer();
        void        ConnectHeartBeats();
        void        SetConnectIp(std::string ip);

        const ConnectData*          GetConnectData();
        const RoomListData*         GetRoomListData();
        const CreateRoomData*       GetCreateRoomData();
        const RefreshRoomData*      GetRefreshRoomData();
        const JoinRoomData*         GetJoinRoomData();
        const UserListData*         GetUserListData();
        const TransmitData*         GetTransmitData();
        const ModifyGameData*       GetModifyGameData();
        const QuitGameData*         GetQuitGameData();
        const RefreshRoomListData*  GetRefreshRoomStatuData();
        const DisconnectData*       GetDisconnectData();
    }

    //void DwordToString(std::std::string &outstr, DWORD dwValue);
}


