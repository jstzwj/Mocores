#ifndef SETTINGS_H
#define SETTINGS_H
#include<string>
#include<memory>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include"filesystem.h"
#include"logerror.h"
#include"errcode.h"

namespace mocores
{
    class Settings
    {
    public:
        Settings();
        int readSettings(const std::string &address,const std::string &encoding);
        int readSettings(const std::string &encoding);
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