#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include<string>

namespace mocores
{
    class LogLevel;
    std::string to_string(const LogLevel & level);
    class LogLevel
    {
    public:
        LogLevel(const std::string& str):level_str(str){}
        friend std::string to_string(const LogLevel & level);
    protected:
        std::string level_str;
    };
    std::string to_string(const LogLevel & level){return level.level_str;}
}


#endif // LOGLEVEL_H
