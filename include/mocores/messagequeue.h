#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H
#include<queue>
#include<cstdint>
namespace mocores
{
    enum MessageTag
    {

    };

    //regular signal
    enum RegularSignal
    {

    };
    class Message
    {
    public:
        MessageTag tagMsg;
        uint32_t time;
    };

    //sigpending
    class MessageQueue
    {
    public:
        MessageQueue();
        void push(Message msg);
        void pop();
        Message front();
        Message back();
        bool getMessage(Message &msg);
        bool peekMessage(Message &msg);
    protected:
        std::queue<Message> queue_impl;
    };
    //signal sender codes
    enum SenderCode
    {
        SI_USER,
        SI_KERNEL,
        SI_QUEUE,
        SI_TIMER,
        SI_ASYNCIO,
        SI_TKILL
    };
    //Flags specifying how to handle a signal
    enum HandleFlags
    {
        SA_NOCLDSTOP,
        SA_NOCLDWAIT,
        SA_SIGINFO,
        SA_ONSTACK,
        SA_RESTART,

        SA_NODEFER, SA_NOMASK,
        SA_RESETHAND,SA_ONESHOT
    };

    //siginfo_t
    class MessageInfo
    {
    public:
        int msg_id;//si_signo: 信号ID
        int err_id;//si_errno: 导致这个信号被发出的错误码. 0 表示不是因为错误才发出信号的 .
        int code;//si_code: 标识谁发出了这个信号
    };
}
#endif // MESSAGEQUEUE_H
