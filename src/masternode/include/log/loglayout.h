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
            std::string result;
            //TODO
            //better string algorithm
			result.reserve(layout.length());
			bool isEscape=false;
			for (unsigned int i = 0; i < layout.length();++i)
			{
				if (isEscape == true)
				{
					switch (layout[i])
					{
					case 'm':
						result.append(msg.getMsg());
						break;
					case 'p':
						result.append(msg.getLevel());
						break;
					case 'r':
						result.append(msg.getTimeFromStart(start_time));
						break;
					case 't':
						result.append(msg.getThreadId());
						break;
					case 'n':
						result.append(msg.getNewLine());
						break;
					case 'd':
					{
						i++;
						if (i<layout.length())
						{
							if (layout[i] == '{')
							{
								i++;
								if (i<layout.length())
								{
									int start_pos = i;
									while (i<layout.length() && layout[i] != '}')
									{
										++i;
									}
									result.append(msg.getTime(layout.substr(start_pos, i - start_pos)));
								}
							}
							else
							{
								result.push_back(layout[i]);
							}
						}
					}
						break;
					default:
						result.push_back(layout[i]);
						break;
					}
					isEscape = false;
					++i;
				}
				else
				{

				}
				if (layout[i] == '%')
				{
					isEscape = true;
				}
				else
				{
					result.push_back(layout[i]);
				}
			}
            return result;
        }
    protected:
        std::string layout;
        TimePoint start_time;
    };
}


#endif // LOGLAYOUT_H
