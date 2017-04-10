#ifndef LOGLAYOUT_H
#define LOGLAYOUT_H

#include<string>
#include<regex>

#include"logmsg.h"

namespace mocores
{

    /*!
     * \brief The LogLayout class
     * \details
     *  %m 输出代码中指定的消息
     *  %p 输出优先级，即DEBUG，INFO，WARN，ERROR，FATAL
     *  %r 输出自应用启动到输出该log信息耗费的毫秒数
     *  %c 输出所属的类目，通常就是所在类的全名
     *  %t 输出产生该日志事件的线程名
     *  %n 输出一个回车换行符，Windows平台为“\r\n”，Unix平台为“\n”
     *  %d 输出日志时间点的日期或时间，默认格式为ISO8601，也可以在其后指定格式，比如：%d{yyy MMM dd HH:mm:ss,SSS}，输出类似：2002年10月18日 22：10：28，921
     *  %l 输出日志事件的发生位置，包括类目名、发生的线程，以及在代码中的行数。举例：Testlog4.main(TestLog4.java:10)
     * \note %c,%l不可用
     */
    class LogLayout
    {
    public:
        using TimePoint=std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
        LogLayout()=default;
        LogLayout(const std::string & _layout):layout(_layout){}
        void setStartTime(const TimePoint& start)
        {
            start_time=start;
        }

        std::string getMsgText(const LogMsg& msg)
        {
            std::string result=layout;
            //TODO
            //better string algorithm
            while(result.find("%m")!=std::string::npos)
                result.replace(result.find("%m"), 2, msg.getMsg());
            while(result.find("%p")!=std::string::npos)
                result.replace(result.find("%p"), 2, msg.getLevel());
            while(result.find("%r")!=std::string::npos)
                result.replace(result.find("%r"), 2, msg.getTimeFromStart(start_time));
            while(result.find("%t")!=std::string::npos)
                result.replace(result.find("%t"), 2, msg.getThreadId());
            while(result.find("%n")!=std::string::npos)
                result.replace(result.find("%n"), 2, msg.getNewLine());
            std::smatch match;
            std::regex timeReg("%d\\{(.*?)\\}");
            while (std::regex_search(result,match,timeReg)) {
                result=match.prefix().str()+msg.getTime(match.format("$1"))+match.suffix().str();
            }
            return result;
        }
    protected:
        std::string layout;
        TimePoint start_time;
    };
}


#endif // LOGLAYOUT_H
