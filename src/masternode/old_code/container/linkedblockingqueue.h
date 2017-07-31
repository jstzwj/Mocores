#ifndef LINKEDBLOCKINGQUEUE_H
#define LINKEDBLOCKINGQUEUE_H
#include<queue>

#include"../thread/mocores_mutex.h"
#include"../thread/mocores_condition_variable.h"

namespace mocores
{
    template<class T>
    class LinkedBlockingQueue
    {
    public:
        LinkedBlockingQueue()
            :running(false),max_size(0){}
        LinkedBlockingQueue(int size)
            :running(false),max_size(size)
        {
            assert(running==false);
            running=true;
        }
        void setMaxSize(int size)
        {
            assert(running==false);
            max_size=size;
            running=true;
        }
        void put(const T& obj)
        {
            mocores::UniqueLock<Mutex> lock(mtx);
            while(isFull())
            {
                notFull.wait(lock);
            }
            data.push(obj);
            notEmpty.notify_one();
        }
        T take()
        {
            mocores::UniqueLock<Mutex> lock(mtx);
            while(isEmpty())
            {
                notEmpty.wait(lock);
            }
            T result=data.front();
            data.pop();
            notFull.notify_one();
            return result;
        }
		bool offer(const T& obj)
		{
			mocores::UniqueLock<Mutex> lock(mtx, std::defer_lock);
			if (lock.try_lock()==true)
			{
				while (isFull())
				{
					notFull.wait(lock);
				}
				data.push(obj);
				notEmpty.notify_one();
				return true;
			}
			else
			{
				return false;
			}
		}
		bool poll(T& obj)
		{
			mocores::UniqueLock<Mutex> lock(mtx, std::defer_lock);
			if (lock.try_lock() == true)
			{
				while (isEmpty())
				{
					notEmpty.wait(lock);
				}
				obj = data.front();
				data.pop();
				notFull.notify_one();
				return true;
			}
			else
			{
				return false;
			}
		}
    protected:
        mocores::Mutex mtx;
        mocores::Condition notEmpty;
        mocores::Condition notFull;
        std::queue<T> data;
        bool running;
        int max_size;

        bool isEmpty()
        {
            return data.size()==0;
        }
        bool isFull()
        {
            if(max_size==0)
            {
                return false;
            }
            if((int)data.size()>=max_size)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };
}
#endif // LINKEDBLOCKINGQUEUE_H
