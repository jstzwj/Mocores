#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

namespace mocores
{
    template<class T>
    class BlockingQueue
    {
    public:
        BlockingQueue()=default;
        virtual void put(const T&obj)=0;
        virtual T take()=0;
    };
}


#endif // BLOCKINGQUEUE_H
