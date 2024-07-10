#pragma once

#include <codecvt>
#include <locale>

#define SAFE_DELETE_PTR(X) if(X != nullptr) { delete X; X = nullptr; }
#define SAFE_DELETE_PTRARRAY(X) if(X != nullptr) { delete[] X; X = nullptr; }

inline std::wstring Utf8ToUnicode(const char* text)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    return cutf8.from_bytes(text);
}

inline std::wstring Utf8ToUnicode(const std::string& text)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    return cutf8.from_bytes(text);
}

inline std::string UnicodeToUtf8(const wchar_t* text)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    return cutf8.to_bytes(text);
}

inline std::string UnicodeToUtf8(const std::wstring& text)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    return cutf8.to_bytes(text);
}

inline void IntToString(std::string& inStr, const int num)
{
    inStr += std::to_string(num);
}

inline void LongToString(std::string& inStr, const long num)
{
    inStr += std::to_string(num);
}


template <class T>
inline void ConvertBitToType(T &t, uint8_t* buf)
{
    size_t size = sizeof(T);
    memcpy(&t, buf, size);
}

inline int ConvertUint8ToInt(uint8_t* buf, const int size)
{
    char* temp = new char[size];
    memcpy(temp, buf, size);
    int val = std::atoi(temp);
    delete [] temp;
    temp = nullptr;
    return val;
}

inline long long ConvertUint8ToLongLong(uint8_t* buf, const int size)
{
    char* temp = new char[size];
    memcpy(temp, buf, size);
    long long val = std::atoll(temp);
    delete[] temp;
    temp = nullptr;
    return val;
}

inline void ConvertUint8ToChar(char* inChar, uint8_t* buf, const int size)
{
    memcpy(inChar, buf, size);
}


std::string Format(const char* format, ...);
std::wstring Format(const wchar_t* format, ...);

std::wstring FormatDateTimeStringW(int64_t timeVal = 0, bool date = true, bool timeOfDay = true);
std::string FormatDateTimeStringA(int64_t timeVal = 0, bool date = true, bool timeOfDay = true);

int CompareVersion(std::wstring& version1, std::wstring& version2);
