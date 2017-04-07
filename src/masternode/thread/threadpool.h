#ifndef THREADPOOL_H
#define THREADPOOL_H


#include<string>
#include<functional>
#include<vector>
#include<deque>

#include"mocores_mutex.h"
#include"mocores_thread.h"
#include"mocores_condition_variable.h"

namespace mocores
{
    class ThreadPool
    {
    public:
        using Task=std::function<void()>;
        ThreadPool();
        ~ThreadPool();
        void start(int num);
    protected:
        Mutex mutex;
        Condition notEmpty;
        Condition notFull;
        std::string name;
        Task threadInitCallback_;
        std::vector<Thread> threads;
        std::deque<Task> queue;
        size_t maxQueueSize;
        bool running;
    };
}


#endif // THREADPOOL_H
