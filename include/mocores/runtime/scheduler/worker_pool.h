#ifndef MOCORES_CLUSTER_WORKER_POOL_H
#define MOCORES_CLUSTER_WORKER_POOL_H

#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

#include <mocores/runtime/scheduler/worker.h>
#include <mocores/runtime/scheduler/work_item.h>

namespace mocores
{
    class WorkerPool
    {
    private:
        std::list<Worker> worker_list;

    public:
        WorkerPool(int worker_num)
        {
            worker_list.resize(worker_num);
        }

        ~WorkerPool()
        {
        }

        void putTask(WorkItem item)
        {

        }
    };
}

#endif