#include "logerror.h"



namespace mocores
{
    LogError errlog;
    LogError::LogError()
    {

    }

    bool LogError::openLogErrorFile(const std::string & filename)
    {
        stream.open(filename,std::ios::out|std::ios::app);
        if(stream.good())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void LogError::log(int logType, const std::string &data)
    {
        stream<<Time::getTime()<<"    ";
        if(logType==1)
        {
            stream<<"[error]";
        }
        else if(logType==2)
        {
            stream<<"[warning]";
        }
        else if(logType==3)
        {
            stream<<"[note]";
        }
        stream<<"    "<<data<<std::endl;
        stream.flush();
    }

    void LogError::closeLogErrorFile()
    {
        stream.close();
    }
}

