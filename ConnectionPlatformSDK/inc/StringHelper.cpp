#include <stdarg.h>
#include <sstream>
#include "TimeHelper.h"
#include "StringHelper.h"

std::string Format(const char* format, ...)
{
    char stringBuf[4096];
    stringBuf[4096 - 1] = 0;

    va_list args;
    va_start(args, format);
    vsnprintf(stringBuf, 4096 - 1, format, args);
    va_end(args);

    return std::string(stringBuf);
}

std::wstring Format(const wchar_t* format, ...)
{
    wchar_t stringBuf[4096];
    stringBuf[4096 - 1] = 0;

    va_list args;
    va_start(args, format);
    vswprintf(stringBuf, 4096 - 1, format, args);
    va_end(args);

    return std::wstring(stringBuf);
}

std::wstring FormatDateTimeStringW(int64_t timeVal, bool date, bool timeOfDay)
{
    tm timeInfo = LocalTime((timeVal == 0)? time(nullptr) : timeVal);

    if (date && !timeOfDay)
    {
        return Format(L"%04d%02d%02d", 
                      timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday);
    }
    else if (!date && timeOfDay)
    {
        return Format(L"%02d%02d%02d", 
                      timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    }
    else
    {
        return Format(L"%04d%02d%02d-%02d%02d%02d",
                      timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
                      timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    }
}

std::string FormatDateTimeStringA(int64_t timeVal, bool date, bool timeOfDay)
{
    tm timeInfo = LocalTime((timeVal == 0)? time(nullptr) : timeVal);

    if (date && !timeOfDay)
    {
        return Format("%04d%02d%02d", 
                      timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday);
    }
    else if (!date && timeOfDay)
    {
        return Format("%02d%02d%02d", 
                      timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    }
    else
    {
        return Format("%04d%02d%02d-%02d%02d%02d",
                      timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
                      timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    }
}

int CompareVersion(std::wstring& version1, std::wstring& version2)
{
    int verParts[2][4] = {};

    for (int i = 0; i < 2; ++i)
    {
        std::wistringstream parser((i == 0)? version1 : version2);
        
        parser >> verParts[i][0];
        for(int j = 1; j < 4; ++j)
        {
            parser.get();
            parser >> verParts[i][j];
        }
    }

    if (std::lexicographical_compare(verParts[0], verParts[0] + 4,
                                     verParts[1], verParts[1] + 4))
    {
        return -1;
    }
    else if (std::lexicographical_compare(verParts[1], verParts[1] + 4,
                                          verParts[0], verParts[0] + 4))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
