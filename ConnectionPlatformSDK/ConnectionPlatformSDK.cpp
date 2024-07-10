// ConnectionPlatformSDK.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "./GameBattleAPI.h"
#include "inc/StringHelper.h"
#include "inc/TimeHelper.h"

#include <sstream>

int main()
{
    LetinvrSDK::SetConnectIp("online.letinvr.com");
    LetinvrSDK::ConnectPlatform("tester","1" ,"1", "1");

    //SleepInMilliseconds(200);
    //for (int i = 0; i < 5; ++i)
    //{
    //    SleepInMilliseconds(200);
    //    LetinvrSDK::ConnectPlatform("tester");
    //    SleepInMilliseconds(200);
    //    LetinvrSDK::CreateGameRoom("teset", "ididid", "roomName", 4);
    //}

    //SleepInMilliseconds(200);
    //LetinvrSDK::GetGameRoomList("teset", "ididid");
    getchar();
}


