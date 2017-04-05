#include "strutil.h"
namespace mocores
{
    StrUtil::StrUtil()
    {

    }

    void StrUtil::consumeSpace(const std::string &str, int &pos)
    {
        while(str[pos]==' '||str[pos]=='\n'||str[pos]=='\t'||str[pos]=='\r')
        {
            ++pos;
        }
    }

    bool StrUtil::isStr(const std::string &str, int &pos, const std::string &match_str)
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
}

