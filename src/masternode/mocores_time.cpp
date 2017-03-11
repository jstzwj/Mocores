#include "mocores_time.h"

namespace mocores
{

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
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);

        result = result.replace(result.find("yyyy"), 4, intToString(1900+(p->tm_year)));
        result = result.replace(result.find("MM"), 2, intToString(1+(p->tm_mon)));
        result = result.replace(result.find("dd"), 2, intToString(p->tm_mday));
        result = result.replace(result.find("HH"), 2, intToString(p->tm_hour));
        result = result.replace(result.find("mm"), 2, intToString(p->tm_min));
        result = result.replace(result.find("ss"), 2, intToString(p->tm_sec));
        return result;
    }

    std::string Time::getTime()
    {
        std::stringstream resultstream;
        std::time_t timep;
        std::tm *p;
        std::time(&timep);
        p = std::gmtime(&timep);
        resultstream<<(1900+(p->tm_year))<<"-"<<(1+(p->tm_mon))<<"-"<<(p->tm_mday)<<"  "
                <<(p->tm_hour)<<":"<<(p->tm_min)<<":"<<(p->tm_sec)<<"  ";
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
