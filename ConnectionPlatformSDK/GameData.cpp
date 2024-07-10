#include "GameData.h"
#include "jaCpp/json.h"
#include "inc/LogManager.h"

int Json_ReadInt(Json::Value JV, int ori_value)
{
    int result = ori_value;
    Json::ValueType VT = JV.type();
    if (VT == Json::ValueType::intValue)
        result = JV.asInt();
    return result;
}
double Json_ReadDouble(Json::Value JV, double ori_value)
{
    double result = ori_value;
    Json::ValueType VT = JV.type();
    if (VT == Json::ValueType::realValue)
        result = JV.asDouble();
    return result;
}

std::string Json_ReadString(Json::Value JV, std::string ori_value)
{
    std::string result = ori_value;
    Json::ValueType VT = JV.type();
    if (VT == Json::ValueType::stringValue)
        result = JV.asCString();
    return result;
}
bool Json_ReadBool(Json::Value JV, bool ori_value)
{
    bool result = ori_value;
    Json::ValueType VT = JV.type();
    if (VT == Json::ValueType::booleanValue)
        result = JV.asBool();
    return result;
}


void GameDataBase::HandleMessage(HeadData &headMes, std::string mes)
{
    m_sHeadMes = headMes;

    if (m_sHeadMes.serialNumber != m_llSendSerial)
    {
        __LogError("serialNumber do not match");
        return;
    }

    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }

    code = Json_ReadString(JsonRoot["code"], code);
    message = Json_ReadString(JsonRoot["msg"], message);
    Json::Value JsonData = JsonRoot["data"];
    JsonData.size();
    if(!data.empty())
        HandleData(JsonData.toStyledString());
}

void ConnectData::HandleData(std::string mes)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }

    sessionid = JsonRoot["sessionid"].asString();
    userNick = JsonRoot["userNick"].asString();
    ip = JsonRoot["ip"].asString();
    port = JsonRoot["port"].asInt();
    userId = JsonRoot["userId"].asString();
}

RoomListData::~RoomListData()
{
    std::vector<RoomInfo>().swap(m_vRoomInfo);
}

void RoomListData::HandleData(std::string mes)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }
    m_vRoomInfo.clear();
    int sz = JsonRoot.size();
    for (int i = 0; i < sz; ++i) {
        RoomInfo info;
        info.roomId = JsonRoot[i]["roomId"].asString();
        info.roomName = JsonRoot[i]["roomName"].asString();
        info.maxNumbers = JsonRoot[i]["maxNumbers"].asInt();
        info.currentNumbers = JsonRoot[i]["currentNumbers"].asInt();
        info.status = JsonRoot[i]["status"].asInt();
        info.custom = JsonRoot[i]["custom"].asString();
        m_vRoomInfo.push_back(info);
    }
}

void CreateRoomData::HandleData(std::string mes)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }
    roomId = JsonRoot["roomId"].asString();
    roomName = JsonRoot["roomName"].asString();
}

JoinRoomData::~JoinRoomData()
{
    std::vector<PlayerInfo>().swap(m_vPlayerInfo);
}

void JoinRoomData::HandleData(std::string mes)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }
    m_vPlayerInfo.clear();
    int sz = JsonRoot.size();
    for (int i = 0; i < sz; ++i) {
        PlayerInfo info;
        info.sessionid = JsonRoot[i]["roomId"].asString();
        info.userNick = JsonRoot[i]["roomName"].asString();
        info.ip = JsonRoot[i]["maxNumbers"].asInt();
        info.port = JsonRoot[i]["currentNumbers"].asInt();
        info.isMaster = JsonRoot[i]["status"].asInt();
        info.custom = JsonRoot[i]["custom"].asString();
        m_vPlayerInfo.push_back(info);
    }
}

UserListData::~UserListData()
{
    std::vector<PlayerInfo>().swap(m_vPlayerInfo);
}

void UserListData::HandleData(std::string mes)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }
    m_vPlayerInfo.clear();
    int sz = JsonRoot.size();
    for (int i = 0; i < sz; ++i) {
        PlayerInfo info;
        info.sessionid = JsonRoot[i]["roomId"].asString();
        info.userNick = JsonRoot[i]["roomName"].asString();
        info.ip = JsonRoot[i]["maxNumbers"].asInt();
        info.port = JsonRoot[i]["currentNumbers"].asInt();
        info.isMaster = JsonRoot[i]["status"].asInt();
        info.custom = JsonRoot[i]["custom"].asString();
        m_vPlayerInfo.push_back(info);
    }
}

void TransmitData::HandleData(std::string mes)
{
    Json::CharReaderBuilder builder;
    Json::CharReader* JsonReader(builder.newCharReader());
    Json::Value JsonRoot, ObjectTmp;
    JSONCPP_STRING errs;
    const char* pstr = mes.c_str();
    if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
    {
        __LogError(L"Read Parse error");
    }

    sessionid = JsonRoot["sessionid"].asString();
    sendUserNick = JsonRoot["sendUserNick"].asString();
    custom = JsonRoot["custom"].asString();
}
