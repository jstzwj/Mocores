#include "clio.h"

namespace mocores
{

    void cliPrint(const char *str)
    {
        std::cout<<str;
    }

    void cliGetline(char *str, int len)
    {
        std::string tmp;
        std::getline(std::cin,tmp);
        int i=0;
        if(len>tmp.length())
        {
            len=tmp.length();
        }
        while(i<len)
        {
            str[i]=tmp[i];
        }
    }

}
