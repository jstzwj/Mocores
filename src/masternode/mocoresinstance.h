#ifndef OPTIONINSTANCE_H
#define OPTIONINSTANCE_H

#include<string>
#include"logerror.h"
namespace mocores
{
    class MocoresInstance
    {
    public:
        MocoresInstance();
        MocoresInstance(const std::string & fileName,const std::string & encoding);
    };
}

#endif // OPTIONINSTANCE_H