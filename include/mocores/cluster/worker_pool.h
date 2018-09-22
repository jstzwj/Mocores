#ifndef MOCORES_CLUSTER_WORKER_POOL_H
#define MOCORES_CLUSTER_WORKER_POOL_H

#include <boost/threadpool.hpp>
#include <vector>

#include <mocores/cluster/worker.h>

namespace mocores
{
    class WorkerPool
    {
    private:
        int worker_num;
        std::vector<Worker> worker_list;
        boost::threadpool::pool worker_pool;

    public:
        WorkerPool(int worker_number)
            :worker_num(worker_number),
            worker_pool(worker_number)
        {
        }




    };
}

#endif