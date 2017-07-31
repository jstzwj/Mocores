#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include<string>

namespace mocores
{
    class LogLevel
    {
    public:
        LogLevel():level_str("ALL"){}
        LogLevel(const std::string& str):level_str(str){}
        std::string to_string()const{return level_str;}
    protected:
        std::string level_str;
        int level_id;
    };

}


#endif // LOGLEVEL_H
