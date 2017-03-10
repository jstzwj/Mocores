#include "settings.h"

namespace mocores
{
    Settings::Settings()
    {

    }

    int Settings::readSettings(const std::string &address, const std::string &encoding)
    {
        //文本读写
        std::fstream settingFile(address,std::ios::in);
        //行缓冲
        std::string line;
        if(settingFile.good())
        {
            errlog.log(3,"Setting file opened.");
        }
        else
        {
            errlog.log(3,"Failed to open setting file.");
        }
        while(!settingFile.eof())
        {
            std::getline(settingFile,line);

            //处理行数据
            int pos=0;
            consumeSpace(line,pos);
            if(isStr(line,pos,"port"))
            {
                consumeSpace(line,pos);
                if(isStr(line,pos,"="))
                {
                    port=atoi(getValue(line,pos).c_str());

                }
            }
            else if(isStr(line,pos,"datadir"))
            {
                consumeSpace(line,pos);
                if(isStr(line,pos,"="))
                {
                    datadir=getString(line,pos);
                }
            }
            else if(isStr(line,pos,"log_error"))
            {
                consumeSpace(line,pos);
                if(isStr(line,pos,"="))
                {
                    log_error=getString(line,pos);
                }
            }
            else if(isStr(line,pos,"bind-address"))
            {
                consumeSpace(line,pos);
                if(isStr(line,pos,"="))
                {
                    bind_address=getValue(line,pos);
                }
            }
        }
        return MOCORES_GOOD;
    }

    int Settings::readSettings(const std::string &encoding)
    {
        return readSettings("option.ini",encoding);
    }

    void Settings::consumeSpace(const std::string &str,int &pos)
    {
        while(str[pos]==' '||str[pos]=='\n'||str[pos]=='\t'||str[pos]=='\r')
        {
            ++pos;
        }
    }

    bool Settings::isStr(const std::string &str, int &pos, const std::string &match_str)
    {
        int match_pos=0;
        while((unsigned int)match_pos<match_str.length()&&
              (unsigned int)(match_pos+pos)<str.length()&&
              str[pos+match_pos]==match_str[match_pos])
        {
            match_pos++;
        }
        if((unsigned int)match_pos==match_str.length())
        {
            pos+=match_pos;
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string Settings::getString(const std::string &str, int pos)
    {
        consumeSpace(str,pos);
        if(str[pos]=='\"')
        {
            std::string result;
            ++pos;
            while((unsigned int)pos<str.length()&&str[pos]!='\"')
            {
                result.push_back(str[pos]);
                ++pos;
            }
            return result;
        }
        else
        {
            return getValue(str,pos);
        }
    }

    std::string Settings::getValue(const std::string &str, int pos)
    {
        consumeSpace(str,pos);
        return str.substr(pos,str.length());
    }
}


