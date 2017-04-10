#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

namespace mocores
{
    template<class T>
    class BlockingQueue
    {
    public:
        BlockingQueue()=default;
        virtual T& front()=0;
        virtual T& back()=0;
        virtual void push()=0;
        virtual void pos()=0;
    };
}


#endif // BLOCKINGQUEUE_H
