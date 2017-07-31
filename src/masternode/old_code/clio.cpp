#include "clio.h"

namespace mocores
{

    void cliPrint(const char *str)
    {
        std::cout<<str;
    }

    void cliGetline(char *str, unsigned int len)
    {
        std::string tmp;
        std::getline(std::cin,tmp);
        unsigned int i=0;
        if((unsigned int)len>tmp.length())
        {
            len=tmp.length();
        }
        while(i<len)
        {
            str[i]=tmp[i];
        }
    }

}
