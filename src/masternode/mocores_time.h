#ifndef MOCORES_TIME_H
#define MOCORES_TIME_H
#include<ctime>
#include<string>
#include<sstream>
#include<algorithm>

namespace mocores
{
    class Time
    {
    public:
        static int getYear();
        static int getMonth();
        static int getDay();
        static int getHour();
        static int getMinute();
        static int getSecond();
        static std::string getTime(const std::string& format);
        static std::string getTime();
    private:
        static bool isStr(const std::string &str, int &pos, const std::string &match_str);
        static std::string intToString(int n);
        static char intToChar(int n);
    };
}

#endif // MOCORES_TIME_H
