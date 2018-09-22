#ifndef MOCORES_CLUSTER_WORKER_POOL_H
#define MOCORES_CLUSTER_WORKER_POOL_H

#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

#include <mocores/cluster/worker.h>

namespace mocores
{
    class WorkerPool
    {
    private:
        int worker_num;
        std::condition_variable ready; // mutex and condition variable for thread pool
        std::mutex mtx;
        std::list<Worker> worker_list;
        int idle;  // idle thread count at the present
        bool quit; // set 1 when destroying thread pool

    public:
        WorkerPool(int worker_number) 
            : worker_num(worker_number), idle(0), quit(0)
        {
            
        }

        ~WorkerPool()
        {
            std::unique_lock <std::mutex> lck(mtx);
            if (quit)
            {
                return;
            }

            quit = 1;
            if (!worker_list.empty())
            {
                // the working thread cannot receive the broadcast notification
                if (idle > 0) cond_broadcast(&pool->ready);

                while (!worker_list.empty())
                {
                    // printf("Waiting thread(s) to exit\n");
                    ready.wait(lck);
                }
            }
        }

        int addWorker(const Worker& worker)
        {
            std::unique_lock <std::mutex> lck(mtx);

            // insert newtask at the end of the queue
            worker_list.push_back(worker);

            // notify waiting threads
            if (idle > 0)
            {
                cond_signal(&pool->ready);
            }
            else if (pool->threadcnt < pool->max_threads)
            { 
                // add new thread if not reaching limit
                pthread_t tid;
                int ret;
                if ((ret = pthread_create(&tid, NULL, thread_routine, (void*)pool)))
                {
                    ERROR("pthread_create", ret);
                }
                pool->threadcnt++;
            }
        }
    };
}

#endif