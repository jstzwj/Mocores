/*
 * @Author: JasonWang
 * @Date: 2018-09-20 17:33:05
 * @LastEditors: JasonWang
 * @LastEditTime: 2018-09-20 17:35:11
 * @Description:
 */

#ifndef MOCORES_CLUSTER_WORKER_H
#define MOCORES_CLUSTER_WORKER_H

#include <memory>
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

#include <mocores/runtime/task.h>

namespace mocores
{
    class Worker
    {
    public:
        Worker();
        ~Worker() {}
        void run()
        {

        }

    private:
        std::list<Task> task_list;
        std::condition_variable ready; // mutex and condition variable for thread pool
        std::mutex mtx;
    };
}

#endif
