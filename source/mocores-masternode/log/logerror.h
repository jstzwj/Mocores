/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/

/*!
    \file logerror.h
    \ingroup main
    \brief Error and success codes
    \version b0001
    \author WangJun <1103870790@qq.com>
    \since build 590
    \par created time:
        2017-03-29 21:35:21 +0800
    \par modified time:
        2017-03-29 21:35:21 +0800
    \par 文本编码:
        UTF-8
    \par 模块名称:
        mocores::LogError
    \see
*/

#ifndef LOGERROR_H
#define LOGERROR_H

#include<string>
#include<fstream>

#include"../mocores_time.h"

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
