#ifndef LOGMSG_H
#define LOGMSG_H

#include<string>
#include<sstream>


#include"../platform.h"
#include"loglevel.h"

#include"../thread/mocores_thread.h"
#include"../mocores_time.h"



namespace mocores
{
    class LogMsg
    {
    public:
        LogMsg():thread_id(),level(),msg(){}
        LogMsg(const LogLevel& _level,const std::string & _msg,Thread::id _id)
            :thread_id(_id),level(_level),msg(_msg){}

        std::string getLevel()const {return level.to_string();}
        std::string getMsg()const {return msg;}
        std::string getThreadId()const
        {
            std::stringstream stream;
            stream<<thread_id;
            return stream.str();
        }
        std::string getNewLine()const
        {
#ifdef MOCORES_OS_WINDOWS
            return "\r\n";
#endif
#ifdef MOCORES_OS_LINUX
            return "\n";
#endif
        }
        std::string getTime(const std::string & format)const
        {
            return Time::getTime(format);
        }
        std::string getTimeFromStart(const std::chrono::time_point<std::chrono::system_clock,std::chrono::nanoseconds> start_time)const
        {
            auto now_time=std::chrono::system_clock::now();
            auto diff=now_time-start_time;
            std::stringstream stream;
            stream<<diff.count();
            return stream.str();
        }

    protected:
        Thread::id thread_id;
        LogLevel level;
        std::string msg;
    };
}
#endif // LOGMSG_H
