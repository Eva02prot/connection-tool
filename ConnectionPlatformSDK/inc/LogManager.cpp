#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>

#include "../inc/StringHelper.h"

#include "LogManager.h"

//extern "C"
//void RegisterLogScreenCallback(CSharpLogScreenCallback callback)
//{
//    logM._logScreenCallback = callback;
//}

// how to use
//__LogInfo(L"开始从本地端口 %d 连接至远程主机 %ls:%d。", localPort, hostNameW.c_str(), hostPort);

void LogManager::LogFormat(bool error, const char* funcName, const char* format, ...)
{
    char msgBuf[1024];
    msgBuf[1024 - 1] = 0;

    va_list args;
    va_start(args, format);
    vsnprintf(msgBuf, 1024 - 1, format, args);
    va_end(args);

    LogMessage(error, funcName, msgBuf);
}

void LogManager::LogFormat(bool error , const char* funcName , const wchar_t* format, ...)
{
    char msgBuf[1024];
    msgBuf[1024 - 1] = 0;

    va_list args;
    va_start(args, format);
    // The vswprinf() doesn't work properly, so we use vsnprintf() instead.
    vsnprintf(msgBuf, 1024 - 1, UnicodeToUtf8(format).c_str(), args);
    va_end(args);

    LogMessage(error, funcName, msgBuf);
}

void LogManager::LogMessage(bool error, const char* funcName, const char* message)
{
    char msgBuf[1024];
    msgBuf[1024 - 1] = 0;
    snprintf(msgBuf, 1024 - 1, "%s: %s", funcName, message);

    WriteLog(msgBuf);
    //if (_logScreenCallback != nullptr)
    //{
    //    _logScreenCallback(error, funcName, message);
    //}
}

void LogManager::GetLogFilePath(char* szPath)
{
    GetModuleFileNameA(NULL, szPath, MAX_PATH);
    ZeroMemory(strrchr(szPath, ('\\')), strlen(strrchr(szPath, ('\\'))) * sizeof(char));
    strcat(szPath, "\\");
    strcat(szPath, LOG_FILE_NAME);
}

void LogManager::ClearLogFile()
{
    char szPath[MAX_PATH] = { 0 };
    GetLogFilePath(szPath);
    std::ofstream fout(szPath, std::ios::out);
    fout.close();
}

std::string LogManager::GetSystemTime()
{
    time_t tNowTime;
    time(&tNowTime);
    tm* tLocalTime = localtime(&tNowTime);
    char szTime[30] = { '\0' };
    strftime(szTime, 30, "[%Y-%m-%d %H:%M:%S] ", tLocalTime);
    std::string strTime = szTime;
    return strTime;
}

void LogManager::WriteLog(char* buf)
{
    char szPath[MAX_PATH] = { 0 };
    GetLogFilePath(szPath);

    std::ofstream fout(szPath, std::ios::app);
    fout.seekp(std::ios::end);
    fout << GetSystemTime() << buf << std::endl;
    fout.close();
}
