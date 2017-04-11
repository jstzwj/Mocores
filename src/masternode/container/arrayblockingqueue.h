#ifndef ARRAYBLOCKINGQUEUE_H
#define ARRAYBLOCKINGQUEUE_H

#include<vector>
#include"../thread/mocores_mutex.h"
#include"../thread/mocores_condition_variable.h"

namespace mocores
{
    template<class T>
    class ArrayBlockingQueue
    {
    public:
        ArrayBlockingQueue()
            :start(0),finish(0),data_size(1024),running(false){}
        ArrayBlockingQueue(int size)
            :start(0),finish(0),data_size(size),running(false)
        {
            assert(running==false);
            data.resize(size);
            running=true;
        }
        void setSize(int size)
        {
            assert(running==false);
            data.resize(size);
            data_size=size;
            running=true;
        }
        void put(const T& obj)
        {
            mocores::UniqueLock<Mutex> lock(mtx);
            while(isFull())
            {
                notFull.wait(lock);
            }
            data[(finish+1)%data_size]=obj;
            finish=(finish+1)%data_size;
            notEmpty.notify_one();
        }
        T take()
        {
            mocores::UniqueLock<Mutex> lock(mtx);
            T result;
            while(isEmpty())
            {
                notEmpty.wait(lock);
            }
            result=data[start];
            start=(start+1)%data_size;
            notFull.notify_one();
            return result;
        }
        bool empty()
        {
            return finish==start;
        }

    protected:
        mocores::Mutex mtx;
        mocores::Condition notEmpty;
        mocores::Condition notFull;
        std::vector<T> data;
        bool running;
        int start;
        int finish;
        int data_size;

        bool isEmpty()
        {
            return start==finish;
        }
        bool isFull()
        {
            return (start+1)%data_size==finish;
        }
    };
}


#endif // ARRAYBLOCKINGQUEUE_H
