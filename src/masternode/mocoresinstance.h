#ifndef OPTIONINSTANCE_H
#define OPTIONINSTANCE_H

#include<string>
#include"logerror.h"
#include"settings.h"
#include"clio.h"
namespace mocores
{
    class MocoresInstance
    {
    public:
        MocoresInstance(mocores::Settings & set);
        int run();
    protected:
        mocores::Settings &setting;
    };
}

#endif // OPTIONINSTANCE_H
