#include "mocores_time.h"

namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
#include <windows.h>
#endif
#ifdef MOCORES_OS_LINUX
#include <time.h>
#endif

    // 获取系统的当前时间，单位微秒(us)
    int64_t Time::GetSysTimeMicros()
    {
    #ifdef _WIN32
    // 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
    #define EPOCHFILETIME   (116444736000000000UL)
        FILETIME ft;
        LARGE_INTEGER li;
        int64_t tt = 0;
        GetSystemTimeAsFileTime(&ft);
        li.LowPart = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
        tt = (li.QuadPart - EPOCHFILETIME) /10;
        return tt;
    #endif
    #ifdef MOCORES_OS_LINUX
        timeval tv;
        gettimeofday(&tv, 0);
        return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
    #endif
        return 0;
    }

    int Time::getYear()
    {
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        return (1900+(p->tm_year));
    }

    int Time::getMonth()
    {
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        return (1+(p->tm_mon));
    }

    int Time::getDay()
    {
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        return (p->tm_mday);
    }

    int Time::getHour()
    {
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        return (p->tm_hour);
    }

    int Time::getMinute()
    {
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        return (p->tm_min);
    }

    int Time::getSecond()
    {
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        return (p->tm_sec);
    }

    std::string Time::getTime(const std::string &format)
    {
        std::string result=format;
        std::time_t timep= std::time(nullptr);
		std::tm *p = std::gmtime(&timep);
		std::stringstream stream;

        while(result.find("%SSS")!=std::string::npos)
            result.replace(result.find("%SSS"), 4, std::to_string(Time::GetSysTimeMicros()));
		stream<<std::put_time(p, result.c_str());
        return stream.str();
    }

    std::string Time::getTime()
    {
        std::stringstream resultstream;
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        resultstream<<(1900+(p->tm_year))<<"-"<<(1+(p->tm_mon))<<"-"<<(p->tm_mday)<<"  "
                <<(p->tm_hour)<<":"<<(p->tm_min)<<":"<<(p->tm_sec)<<"  "<<Time::GetSysTimeMicros()<<" ";
        return resultstream.str();
    }

    bool Time::isStr(const std::string &str, int &pos, const std::string &match_str)
    {
        int match_pos=0;
        while((unsigned int)match_pos<match_str.length()&&
              (unsigned int)(match_pos+pos)<str.length()&&
              str[pos+match_pos]==match_str[match_pos])
        {
            match_pos++;
        }
        if((unsigned int)match_pos==match_str.length())
        {
            pos+=match_pos;
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string Time::intToString(int n)
    {
        std::string result;
        while(n!=0)
        {
            result.push_back(n%10);
            n=n/10;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    char Time::intToChar(int n)
    {
        return n+'0';
    }


}
