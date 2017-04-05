#include "strutil.h"
namespace mocores
{
    StrUtil::StrUtil()
    {

    }

    bool StrUtil::isInCharRange(char c, char min, char max)
    {
        if(c>=min&&c<=max)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool StrUtil::isSameChar(char lhs, char rhs, StrMatchMode mode)
    {
        if(mode==MOCORES_STRUTIL_CASE_SENSITIVE)
        {
            return lhs==rhs;
        }
        else if(mode==MOCORES_STRUTIL_NON_CASE_SENSITIVE)
        {
            if(isInCharRange(lhs,'a','z')&&isInCharRange(lhs,'A','Z')&&
                    isInCharRange(rhs,'a','z')&&isInCharRange(rhs,'A','Z'))
            {
                return (abs(rhs-lhs)=='0')||(lhs==rhs);
            }
            else
            {
                return false;
            }
        }
    }

    void StrUtil::consumeSpace(const std::string &str, int &pos)
    {
        while(str[pos]==' '||str[pos]=='\n'||str[pos]=='\t'||str[pos]=='\r')
        {
            ++pos;
        }
    }

    bool StrUtil::isStr(const std::string &str, int &pos, const std::string &match_str,StrMatchMode mode)
    {
        int match_pos=0;
        while((unsigned int)match_pos<match_str.length()&&
              (unsigned int)(match_pos+pos)<str.length()&&
              isSameChar(str[pos+match_pos],match_str[match_pos],mode))
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

