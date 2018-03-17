#include "threadpool.h"
namespace mocores
{
    ThreadPool::ThreadPool()
        : mutex(),
            notEmpty(),
            notFull(),
            name(),
            maxQueueSize(0),
            running(false)
    {

    }

    ThreadPool::~ThreadPool()
    {
        if (running)
        {
            stop();
        }
        for(auto &each:threads)
        {
            delete each;
        }
    }

    void ThreadPool::start(int num, int maxSize)
    {
        assert(threads.empty());
        maxQueueSize=maxSize;
        running = true;
        threads.reserve(num);
        for (int i = 0; i < num; ++i)
        {
          char id[32];
          snprintf(id, sizeof id, "%d", i+1);
          threads.push_back(new Thread(std::bind(&ThreadPool::runInThread, this), name+id));
        }
        if (num == 0 && threadInitCallback)
        {
          threadInitCallback();
        }
    }

    void ThreadPool::stop()
    {
        {
          mocores::UniqueLock<mocores::Mutex> lock(mutex);
          UNUSED(lock);
          running = false;
          notEmpty.notify_all();
        }
        for(auto & each:threads)
        {
            each->join();
        }
    }

    void ThreadPool::run(const ThreadPool::Task &task)
    {
        if (threads.empty())
        {
           task();
        }
        else
        {
            mocores::UniqueLock<mocores::Mutex> lock(mutex);
            while (isFull())
            {
              notFull.wait(lock);
            }
            assert(!isFull());
            queue.push_back(task);
            notEmpty.notify_one();
        }
    }
    /*!
     * \note mutex被锁住才可调用
     */
    bool ThreadPool::isFull() const
    {
      return maxQueueSize> 0 && queue.size() >= maxQueueSize;
    }

    ThreadPool::Task ThreadPool::take()
    {
        mocores::UniqueLock<mocores::Mutex> lock(mutex);
        // always use a while-loop, due to spurious wakeup
        while (queue.empty() && running)
        {
          notEmpty.wait(lock);
        }
        Task task;
        if (!queue.empty())
        {
          task = queue.front();
          queue.pop_front();
          if (maxQueueSize > 0)
          {
            notFull.notify_one();
          }
        }
        return task;
    }

    void ThreadPool::runInThread()
    {
        try
        {
          if (threadInitCallback)
          {
            threadInitCallback();
          }
          while (running)
          {
            Task task(take());
            if (task)
            {
              task();
            }
          }
        }
        catch (const std::exception& ex)
        {
            std::cerr<<"exception caught in ThreadPool %s\n"<<name<<std::endl;
            std::cerr<<"reason: %s\n"<<ex.what()<<std::endl;
            abort();
        }
        catch (...)
        {
            std::cerr<<"unknown exception caught in ThreadPool %s\n"<<name<<std::endl;
            throw; // rethrow
        }
    }
}

