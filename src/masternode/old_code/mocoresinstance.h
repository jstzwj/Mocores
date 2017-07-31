/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/
/*!
    \file mocoresinstance.h
    \ingroup main
    \brief The instance of mocores master node
    \version b0001
    \author WangJun <1103870790@qq.com>
    \since b0001
    \par created time:
        2017-03-29 21:35:21 +0800
    \par modified time:
        2017-03-30 13:20:28 +0800
    \par text encoding:
        UTF-8
    \par module name:
        mocores::MocoresInstance
*/
#ifndef OPTIONINSTANCE_H
#define OPTIONINSTANCE_H

#include<string>
#include<memory>
#include"log/logger.h"
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
