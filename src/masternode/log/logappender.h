#ifndef LOGAPPENDER_H
#define LOGAPPENDER_H

#include<ostream>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

namespace mocores
{
    class LogAppender
    {
    public:
        LogAppender()=default;
        /*inner function*/
        virtual int open()=0;
        /*inner function*/
        virtual void close()=0;
        virtual void append(const std::string & str)=0;
        virtual void flush()=0;
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
        virtual int open(){return 0;}
        virtual void close(){return;}
        virtual void append(const std::string & str)
        {
            out<<str;
        }
        virtual void flush()
        {
            out.flush();
        }

    protected:
        std::ostream & out;
    };

    class FileAppender:public LogAppender
    {
    public:
        FileAppender(const std::string& filepath)
            :path(filepath){}
        ~FileAppender()
        {
            delete fstream;
            fstream=nullptr;
        }
        virtual int open()
        {
            fstream=new std::ofstream(path,std::ios::out|std::ios::app);
            if(!fstream->good())
                return 0;
            else
                return 1;
        }

        virtual void close()
        {
            fstream->close();
        }

        virtual void append(const std::string & str)
        {
            (*fstream)<<str;
        }
        virtual void flush()
        {
            fstream->flush();
        }

    protected:
        std::ofstream *fstream;
        std::string path;
    };

}

#endif // LOGAPPENDER_H
