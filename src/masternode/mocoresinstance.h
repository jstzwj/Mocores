#ifndef OPTIONINSTANCE_H
#define OPTIONINSTANCE_H

#include<string>
#include<memory>
#include"logerror.h"
#include"settings.h"
#include"clio.h"
#include"messagequeue.h"
#include"./thread/mocores_mutex.h"
#include"./thread/mocores_thread.h"
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
