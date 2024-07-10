#pragma once
#include <windows.h>

#define LOG_FILE_NAME "MyLog.txt"

#define LOG_ENABLE

#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class CLog    
{    
public:

    static void GetLogFilePath(char* szPath)
    {
        GetModuleFileNameA( NULL, szPath, MAX_PATH );
        ZeroMemory(strrchr(szPath,('\\')), strlen(strrchr(szPath,('\\') ) )*sizeof(char)) ;
        strcat(szPath, "\\");
        strcat(szPath, LOG_FILE_NAME);
    }

    static void Clear()
    {
        char szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);
        ofstream fout(szPath,ios::out);
        fout.close();
    }


    template <class T>
    static void WriteLog(T x)
    {
        char szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);

        ofstream fout(szPath,ios::app);
        fout.seekp(ios::end);
        fout << GetSystemTime() << x <<endl;
        fout.close();  
    }

    template<class T1,class T2>
    static void WriteLog2(T1 x1, T2 x2)
    {  
        char szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);  
        ofstream fout(szPath,ios::app);
        fout.seekp(ios::end);
        fout << GetSystemTime() << x1 <<" = "<<x2<<endl;
        fout.close();
    }  

    template <class T>  
    static void WriteFuncBegin(T x)
    {  
        char szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);
        ofstream fout(szPath,ios::app);
        fout.seekp(ios::end);  
        fout << GetSystemTime() << "    --------------------"<<x<<"  Begin--------------------" <<endl;  
        fout.close();  
    }  

    template <class T>  
    static void WriteFuncEnd(T x)  
    {  
        char szPath[MAX_PATH] = {0};  
        GetLogFilePath(szPath);  
        ofstream fout(szPath,ios::app);  
        fout.seekp(ios::end);  
        fout << GetSystemTime() << "--------------------"<<x<<"  End  --------------------" <<endl;  
        fout.close();  
    }

private:
    static string GetSystemTime()
    {    
        time_t tNowTime;
        time(&tNowTime);
        tm* tLocalTime = localtime(&tNowTime);
        char szTime[30] = {'\0'};
        strftime(szTime, 30, "[%Y-%m-%d %H:%M:%S] ", tLocalTime);
        string strTime = szTime;
        return strTime;
    }
};

#ifdef LOG_ENABLE 
#define LOG(x)          CLog::WriteLog(x);
#define LOG2(x1, x2)     CLog::WriteLog2(x1, x2);
#define LOG_FUNC        LOG(__FUNCTION__)
#define LOG_LINE        LOG(__LINE__)
#define LOG_FUNC_BEGIN  CLog::WriteFuncBegin(__FUNCTION__);
#define LOG_FUNC_END    CLog::WriteFuncEnd(__FUNCTION__);
#define LOGCLEAR        CLog::Clear();

#else  

#define LOG(x)
#define LOG2(x1,x2)
#define LOG_FUNC
#define LOG_LINE
#define LOG_FUNC_BEGIN
#define LOG_FUNC_END
#define LOGCLEAR

#endif

