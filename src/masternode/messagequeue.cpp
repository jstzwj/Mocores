#include "messagequeue.h"
namespace mocores
{
    MessageQueue::MessageQueue()
    {

    }

    void MessageQueue::push(Message msg)
    {
        this->queue_impl.push(msg);
    }

    void MessageQueue::pop()
    {
        this->queue_impl.pop();
    }

    Message MessageQueue::front()
    {
        return queue_impl.front();
    }

    Message MessageQueue::back()
    {
        return queue_impl.back();
    }

    bool MessageQueue::getMessage(Message &msg)
    {
        if(queue_impl.empty())
        {
            return false;
        }
        else
        {
            msg=queue_impl.front();
            queue_impl.pop();
            return true;
        }
    }

    bool MessageQueue::peekMessage(Message &msg)
    {
        if(queue_impl.empty())
        {
            return false;
        }
        else
        {
            msg=queue_impl.front();
            return true;
        }
    }

}

