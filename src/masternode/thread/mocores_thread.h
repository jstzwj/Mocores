#ifndef THREAD_H
#define THREAD_H
#include<cstdint>
#include<thread>
#include<chrono>
#include"../platform.h"
namespace mocores
{
    using Thread=std::thread;
    namespace this_thread {
        using namespace std::this_thread;
    }
}


#endif // THREAD_H
