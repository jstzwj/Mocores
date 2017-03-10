#ifndef LOGERROR_H
#define LOGERROR_H

#include<string>
#include<ctime>
#include<fstream>

namespace mocores
{
    class LogError
    {
    public:
        LogError();
        bool openLogErrorFile(const std::string &filename);
        void log(int logType,const std::string & data);//0:error,1:warning,2note
        void closeLogErrorFile();
    private:
        std::fstream stream;
    };
    extern LogError errlog;
}


#endif // LOGERROR_H
