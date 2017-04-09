#ifndef LOGAPPENDER_H
#define LOGAPPENDER_H

#include<ostream>
#include<iostream>
#include<fstream>
#include<string>

namespace mocores
{
    class LogAppender
    {
    public:
        LogAppender()=default;
        LogAppender(const LogAppender&other)=delete;
        LogAppender& operator =(const LogAppender&other)=delete;
        virtual void append(const std::string & str)=0;
    };

    /*!
     *  \brief default ostream
     *  \details ConsoleAppender（控制台），
     *           FileAppender（文件），
     *           以下暂时不支持
     *           DailyRollingFileAppender（每天产生一个日志文件），
     *           RollingFileAppender（文件大小到达指定尺寸的时候产生一个新的文件），
     *           WriterAppender（将日志信息以流格式发送到任意指定的地方）
     */
    class ConsoleAppender:public LogAppender
    {
    public:
        ConsoleAppender():out(std::cout){}
        virtual void append(const std::string & str)
        {
            out<<str;
        }
    protected:
        std::ostream & out;
    };

    class FileAppender:public LogAppender
    {
    public:
        FileAppender(const std::string& path)
        {
            fstream=new std::ofstream(path,std::ios::out|std::ios::app);
        }
        ~FileAppender()
        {
            delete fstream;
        }
        virtual void append(const std::string & str)
        {
            (*fstream)<<str;
        }
    protected:
        std::ofstream *fstream;
    };

}

#endif // LOGAPPENDER_H
