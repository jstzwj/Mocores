/*
 * @Author: JasonWang
 * @Date: 2018-09-20 17:33:05
 * @LastEditors: JasonWang
 * @LastEditTime: 2018-09-20 17:35:11
 * @Description:
 */

#ifndef MOCORES_CLUSTER_WORKER_H
#define MOCORES_CLUSTER_WORKER_H

#include <condition_variable>
#include <list>
#include <memory>
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
            while (true)
            {
                std::unique_lock<std::mutex> lck(m_mtx);
                while (task_list.empty())
                {
                    ready.wait(lck);
                }
                Task& front_task = task_list.front();
                // TODO run task
                
                task_list.pop_front();
            }
        }

        void putTask(const Task& task)
        {
            while (true)
            {
                std::unique_lock<std::mutex> lck(mtx);
                task_list.push_back(task);
                ready.notify_all();
            }
        }

    private:
        std::list<Task> task_list;
        std::condition_variable ready; // mutex and condition variable for thread pool
        std::mutex mtx;
    };
}

#endif
