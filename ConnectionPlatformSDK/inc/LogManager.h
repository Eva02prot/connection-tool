#pragma once

#include <windows.h>
#include <fstream>
#include <string>

#define LOG_FILE_NAME "MyLog.txt"
#define LOG_ENABLE

typedef void (*CSharpLogScreenCallback)(bool error, const char* funcName, const char* message);

namespace LogManager
{
    void LogFormat(bool error, const char* funcName, const char* format, ...);
    void LogFormat(bool error, const char* funcName, const wchar_t* format, ...);

    void LogMessage(bool error, const char* funcName, const char* message);

    void GetLogFilePath(char* szPath);
    void ClearLogFile();
    std::string GetSystemTime();
    void WriteLog(char* buf);
};

#define __LogInfo(...) LogManager::LogFormat(false, __func__, __VA_ARGS__)
#define __LogError(...) LogManager::LogFormat(true, __func__, __VA_ARGS__)
