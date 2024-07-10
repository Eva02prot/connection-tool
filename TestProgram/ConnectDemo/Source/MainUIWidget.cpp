// Fill out your copyright notice in the Description page of Project Settings.

#include "MainUIWidget.h"

#include "../ThirdParty/include/GameBattleAPI.h"
#include "../ThirdParty/include/GameData.h"

UMainUIWidget::UMainUIWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

bool UMainUIWidget::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }

    m_eDataType = DataType::DEFAULTTYPE;

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_1")))
    {
        Button_1 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_1"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button1Click");
        Button_1->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_2")))
    {
        Button_2 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_2"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button2Click");
        Button_2->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_3")))
    {
        Button_3 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_3"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button3Click");
        Button_3->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_4")))
    {
        Button_4 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_4"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button4Click");
        Button_4->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_5")))
    {
        Button_5 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_5"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button5Click");
        Button_5->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_6")))
    {
        Button_6 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_6"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button6Click");
        Button_6->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_7")))
    {
        Button_7 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_7"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button7Click");
        Button_7->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_8")))
    {
        Button_8 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_8"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button8Click");
        Button_8->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_9")))
    {
        Button_9 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_9"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button9Click");
        Button_9->OnClicked.Add(sgbDelegate);
    }

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("Button_10")))
    {
        Button_10 = SBtn;
        UE_LOG(LogTemp, Warning, TEXT("Button_10"));

        FScriptDelegate sgbDelegate;
        sgbDelegate.BindUFunction(this, "Button10Click");
        Button_10->OnClicked.Add(sgbDelegate);
    }

    if (UScrollBox* scrollBox = Cast<UScrollBox>(GetWidgetFromName("ScrollBox_1")))
    {
        ScrollBox_1 = scrollBox;
    }

    if (UTextBlock* code = Cast<UTextBlock>(GetWidgetFromName("TextBox_Code")))
    {
        TextBlock_Code = code;
    }

    if (UTextBlock* roomID = Cast<UTextBlock>(GetWidgetFromName("TextBlock_RoomID")))
    {
        TextBlock_RoomID = roomID;
    }

    if (UEditableTextBox* index = Cast<UEditableTextBox>(GetWidgetFromName("TextBlock_RoomID")))
    {
        EditableBox_RoomIndex = index;
    }
    
    if (UTextBlock* message = Cast<UTextBlock>(GetWidgetFromName("TextBox_Message")))
    {
        TextBlock_Message = message;
    }

    return true;
}

void UMainUIWidget::UpdateData()
{
    switch (m_eDataType)
    {
    case DEFAULTTYPE:
        break;
    case CONNECT:
        SetConnectData();
        break;
    case ROOMLIST:
        SetGameRoomData();
        break;
    case CREATEROOM:
        SetCreateRoomData();
        break;
    case JOINROOM:
        SetJoinGameData();
        break;
    case REFRESHROOMINFO:
        SetRoomInfoData();
        break;
    case USERLIST:
        SetUserListData();
        break;
    case USERINFO:
        SetModifyUserData();
        break;
    case LEAVEROOM:
        SetQuitRoomData();
        break;
    case ROOMSTATUS:
        SetGameStatusData();
        break;
    case DISCONNECT:
        SetDisconnectData();
        break;
    default:
        break;
    }
}

void UMainUIWidget::SetConnectData()
{
    FString strCode = LetinvrSDK::GetConnectData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetConnectData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));

    ScrollBox_1->ClearChildren();
    UCustomUserWidget* widget = CreateWidget<UCustomUserWidget>(GetWorld(), WidgetClass);

    ScrollBox_1->AddChild(widget);
    widget->SetVisibility(ESlateVisibility::Visible);


    if (widget != nullptr)
    {
        std::string temStr;

        temStr = "sessionid:" + LetinvrSDK::GetConnectData()->sessionid;
        widget->SetTextByIndex(FString(temStr.c_str()), 1);

        temStr = "userNick:" + LetinvrSDK::GetConnectData()->userNick;
        widget->SetTextByIndex(FString(temStr.c_str()), 2);

        temStr = "ip:" + LetinvrSDK::GetConnectData()->ip;
        widget->SetTextByIndex(FString(temStr.c_str()), 3);

        temStr = "port:" + std::to_string(LetinvrSDK::GetConnectData()->port);
        widget->SetTextByIndex(FString(temStr.c_str()), 4);
    }
}

void UMainUIWidget::SetGameRoomData()
{
    FString strCode = LetinvrSDK::GetRoomListData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetRoomListData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));

    auto list = LetinvrSDK::GetRoomListData()->m_vRoomInfo;
    int listSize = list.size();

    m_vRoomID.clear();

    UCustomUserWidget* widget = nullptr;

    ScrollBox_1->ClearChildren();

    for (int i = 0; i < listSize; ++i)
    {
        widget = CreateWidget<UCustomUserWidget>(GetWorld(), WidgetClass);
        ScrollBox_1->AddChild(widget);
        widget->SetVisibility(ESlateVisibility::Visible);

        if (widget != nullptr)
        {
            std::string temStr;

            temStr = "roomId:" + list[i].roomId;
            m_vRoomID.push_back(list[i].roomId);
            widget->SetTextByIndex(FString(temStr.c_str()), 1);

            temStr = "roomName:" + list[i].roomName;
            widget->SetTextByIndex(FString(temStr.c_str()), 2);

            temStr = "maxNumbers:" + std::to_string(list[i].maxNumbers);
            widget->SetTextByIndex(FString(temStr.c_str()), 3);

            temStr = "currentNumbers:" + std::to_string(list[i].currentNumbers);
            widget->SetTextByIndex(FString(temStr.c_str()), 4);

            temStr = "status:" + std::to_string(list[i].status);
            widget->SetTextByIndex(FString(temStr.c_str()), 5);

            temStr = "custom:" + list[i].custom;
            widget->SetTextByIndex(FString(temStr.c_str()), 6);
        }
    }
}

void UMainUIWidget::SetCreateRoomData()
{
    FString strCode = LetinvrSDK::GetCreateRoomData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetCreateRoomData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));

    ScrollBox_1->ClearChildren();
    UCustomUserWidget* widget = CreateWidget<UCustomUserWidget>(GetWorld(), WidgetClass);

    ScrollBox_1->AddChild(widget);
    widget->SetVisibility(ESlateVisibility::Visible);
    
    if (widget != nullptr)
    {
        std::string temStr;

        temStr = "roomId:" + LetinvrSDK::GetCreateRoomData()->roomId;
        widget->SetTextByIndex(FString(temStr.c_str()), 1);

        temStr = "roomName:" + LetinvrSDK::GetCreateRoomData()->roomName;
        widget->SetTextByIndex(FString(temStr.c_str()), 2);
    }
}

void UMainUIWidget::SetJoinGameData()
{
    FString strCode = LetinvrSDK::GetJoinRoomData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetJoinRoomData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));

    auto list = LetinvrSDK::GetJoinRoomData()->m_vPlayerInfo;
    int listSize = list.size();

    UCustomUserWidget* widget = nullptr;

    ScrollBox_1->ClearChildren();

    for (int i = 0; i < listSize; ++i)
    {

        widget = CreateWidget<UCustomUserWidget>(GetWorld(), WidgetClass);
        ScrollBox_1->AddChild(widget);
        widget->SetVisibility(ESlateVisibility::Visible);

        if (widget != nullptr)
        {
            std::string temStr;

            temStr = "ip:" + list[i].ip;
            widget->SetTextByIndex(FString(temStr.c_str()), 1);

            temStr = "port:" + std::to_string(list[i].port);
            widget->SetTextByIndex(FString(temStr.c_str()), 2);

            temStr = "sessionid:" + list[i].sessionid;
            widget->SetTextByIndex(FString(temStr.c_str()), 3);

            temStr = "userNick:" + list[i].userNick;
            widget->SetTextByIndex(FString(temStr.c_str()), 4);

            temStr = "isMaster:" + std::to_string(list[i].isMaster);
            widget->SetTextByIndex(FString(temStr.c_str()), 5);

            temStr = "custom:" + list[i].custom;
            widget->SetTextByIndex(FString(temStr.c_str()), 6);
        }
    }
}

void UMainUIWidget::SetRoomInfoData()
{
    FString strCode = LetinvrSDK::GetRefreshRoomData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetRefreshRoomData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));
    ScrollBox_1->ClearChildren();
}

void UMainUIWidget::SetUserListData()
{
    FString strCode = LetinvrSDK::GetUserListData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetUserListData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));

    auto list = LetinvrSDK::GetUserListData()->m_vPlayerInfo;
    int listSize = list.size();

    UCustomUserWidget* widget = nullptr;

    ScrollBox_1->ClearChildren();

    for (int i = 0; i < listSize; ++i)
    {
        widget = CreateWidget<UCustomUserWidget>(GetWorld(), WidgetClass);
        ScrollBox_1->AddChild(widget);
        widget->SetVisibility(ESlateVisibility::Visible);

        if (widget != nullptr)
        {
            std::string temStr;

            temStr = "ip:" + list[i].ip;
            widget->SetTextByIndex(FString(temStr.c_str()), 1);

            temStr = "port:" + std::to_string(list[i].port);
            widget->SetTextByIndex(FString(temStr.c_str()), 2);

            temStr = "sessionid:" + list[i].sessionid;
            widget->SetTextByIndex(FString(temStr.c_str()), 3);

            temStr = "userNick:" + list[i].userNick;
            widget->SetTextByIndex(FString(temStr.c_str()), 4);

            temStr = "isMaster:" + std::to_string(list[i].isMaster);
            widget->SetTextByIndex(FString(temStr.c_str()), 5);

            temStr = "custom:" + list[i].custom;
            widget->SetTextByIndex(FString(temStr.c_str()), 6);
        }
    }
}

void UMainUIWidget::SetModifyUserData()
{
    FString strCode = LetinvrSDK::GetModifyGameData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetModifyGameData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));
    ScrollBox_1->ClearChildren();
}

void UMainUIWidget::SetQuitRoomData()
{
    FString strCode = LetinvrSDK::GetQuitGameData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetQuitGameData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));
    ScrollBox_1->ClearChildren();
}

void UMainUIWidget::SetGameStatusData()
{
    FString strCode = LetinvrSDK::GetRefreshRoomStatuData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetRefreshRoomStatuData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));
    ScrollBox_1->ClearChildren();
}

void UMainUIWidget::SetDisconnectData()
{
    FString strCode = LetinvrSDK::GetDisconnectData()->code.c_str();
    TextBlock_Code->SetText(FText::FromString(strCode));
    FString strMessage = UTF8_TO_TCHAR(LetinvrSDK::GetDisconnectData()->message.c_str());
    TextBlock_Message->SetText(FText::FromString(strMessage));
    ScrollBox_1->ClearChildren();
}

void UMainUIWidget::SendHeartBeat()
{
    LetinvrSDK::ConnectHeartBeats();
}

void UMainUIWidget::Button1Click()
{
    //LetinvrSDK::SetConnectIp("online.letinvr.com");
    LetinvrSDK::ConnectPlatform("Tester", "Tester", "Tester", "Tester");
    GetWorld()->GetTimerManager().SetTimer(m_hHeartBeatHandel, this, &UMainUIWidget::SendHeartBeat, 3.0f, true, 0.1f);
    m_eDataType = DataType::CONNECT;

}

void UMainUIWidget::Button2Click()
{
    LetinvrSDK::GetGameRoomList("teset", "ididid");
    m_eDataType = DataType::ROOMLIST;


}

void UMainUIWidget::Button3Click()
{
    LetinvrSDK::CreateGameRoom("teset", "ididid", "TestRoom", 4, "ttttt");

    m_eDataType = DataType::CREATEROOM;
}

void UMainUIWidget::Button4Click()
{
    FText roomID = EditableBox_RoomIndex->GetText();

    FString intStr = EditableBox_RoomIndex->GetText().ToString();
    int32 index = FCString::Atoi(*intStr) - 1;

    if (index != -1 && index < m_vRoomID.size())
    {
        LetinvrSDK::JoinGameRoom(m_vRoomID[index]);
        TextBlock_RoomID->SetText(FText::FromString(FString(m_vRoomID[index].c_str())));
    }

    m_eDataType = DataType::JOINROOM;
}

void UMainUIWidget::Button5Click()
{

    FText roomID = EditableBox_RoomIndex->GetText();

    FString intStr = EditableBox_RoomIndex->GetText().ToString();
    int32 index = FCString::Atoi(*intStr) - 1;
    if (index != -1 && index < m_vRoomID.size())
    {
        LetinvrSDK::RefreshRoomInfo(m_vRoomID[index] , "ttttt");
        TextBlock_RoomID->SetText(FText::FromString(FString(m_vRoomID[index].c_str())));
    }

    m_eDataType = DataType::REFRESHROOMINFO;
}

void UMainUIWidget::Button6Click()
{

    FText roomID = EditableBox_RoomIndex->GetText();

    FString intStr = EditableBox_RoomIndex->GetText().ToString();
    int32 index = FCString::Atoi(*intStr) - 1;
    if (index != -1 && index < m_vRoomID.size())
    {
        LetinvrSDK::GetGameRoomUserList(m_vRoomID[index]);
        TextBlock_RoomID->SetText(FText::FromString(FString(m_vRoomID[index].c_str())));
    }

    m_eDataType = DataType::USERLIST;
}

void UMainUIWidget::Button7Click()
{
    LetinvrSDK::ModifyUserStatus("ttttttt");

    m_eDataType = DataType::USERINFO;
}

void UMainUIWidget::Button8Click()
{
    FText roomID = EditableBox_RoomIndex->GetText();

    FString intStr = EditableBox_RoomIndex->GetText().ToString();
    int32 index = FCString::Atoi(*intStr) - 1;
    if (index != -1 && index < m_vRoomID.size())
    {
        LetinvrSDK::RefreshRoomStatus(m_vRoomID[index], 1);
        TextBlock_RoomID->SetText(FText::FromString(FString(m_vRoomID[index].c_str())));
    }
    m_eDataType = DataType::ROOMSTATUS;
}

void UMainUIWidget::Button9Click()
{
    LetinvrSDK::DisconnectPlatform();

    GetWorld()->GetTimerManager().ClearTimer(m_hHeartBeatHandel);
    std::vector<std::string>().swap(m_vRoomID);

    m_eDataType = DataType::DISCONNECT;
}

void UMainUIWidget::Button10Click()
{
    FText roomID = EditableBox_RoomIndex->GetText();

    FString intStr = EditableBox_RoomIndex->GetText().ToString();
    int32 index = FCString::Atoi(*intStr) - 1;
    if (index != -1 && index < m_vRoomID.size())
    {
        LetinvrSDK::QuitGameRoom(m_vRoomID[index]);
        TextBlock_RoomID->SetText(FText::FromString(FString(m_vRoomID[index].c_str())));
    }

    m_eDataType = DataType::LEAVEROOM;
}
