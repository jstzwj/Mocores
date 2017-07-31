#ifndef THREADPOOL_H
#define THREADPOOL_H


#include<string>
#include<functional>
#include<vector>
#include<deque>
#include<iostream>
#include<algorithm>

#include<cassert>

#include"mocores_mutex.h"
#include"mocores_thread.h"
#include"mocores_condition_variable.h"

#include"../platform.h"

namespace mocores
{
    class ThreadPool
    {
    public:
        using Task=std::function<void()>;
        ThreadPool();
        ThreadPool(const ThreadPool &)=delete;
        ThreadPool operator =(const ThreadPool &)=delete;
        ~ThreadPool();

        void setThreadInitCallback(const Task& cb){ threadInitCallback = cb; }

        void start(int num,int maxSize);
        void stop();
        void run(const Task &task);
        bool isFull() const;
        Task take();
        void runInThread();
    protected:
        Mutex mutex;
        Condition notEmpty;
        Condition notFull;
        std::string name;
        Task threadInitCallback;
        std::vector<Thread*> threads;
        std::deque<Task> queue;
        size_t maxQueueSize;
        bool running;
    };
}


#endif // THREADPOOL_H
