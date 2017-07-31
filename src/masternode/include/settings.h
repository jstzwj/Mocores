/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/

/*!
\file settings.h
\ingroup main
\brief The settings read from mocores setting file.
\version b0001
\author WangJun <1103870790@qq.com>
\since b0001
\par created time:
    2017-03-29 21:35:21 +0800
\par modified time:
    2017-03-30 11:36:53 +0800
\par text encoding:
    UTF-8
\par module name:
    mocores::Settings
\see
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include<string>
#include<memory>
#include<fstream>
#include<cstdlib>

#include"filesystem/filesystem.h"
#include"log/logger.h"
#include"errcode.h"
#include"clio.h"

namespace mocores
{
    /*!
     * \brief The Settings class read from setting file
     */
    class Settings
    {
    public:
        Settings();
        int readSettings(const std::string &address);
        int readSettings();
    protected:
        void consumeSpace(const std::string &str, int &pos);
        bool isStr(const std::string &str,int &pos,const std::string &match_str);
        std::string getString(const std::string &str,int pos);
        std::string getValue(const std::string &str,int pos);
    public:
        int port;
        std::string basedir;
        std::string datadir;
        std::string bind_address;
        std::string log_error;
        int sqlMode;
    };
}


#endif // SETTINGS_H
