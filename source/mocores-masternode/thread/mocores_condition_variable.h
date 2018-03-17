#ifndef MOCORES_CONDITION_VARIABLE_H
#define MOCORES_CONDITION_VARIABLE_H

#include<condition_variable>
#include<chrono>
#include"mocores_mutex.h"
namespace mocores
{
    using Condition=std::condition_variable;
}
#endif // MOCORES_CONDITION_VARIABLE_H
