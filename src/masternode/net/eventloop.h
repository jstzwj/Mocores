#ifndef EVENTLOOP_H
#define EVENTLOOP_H

namespace mocores
{
    class EventLoop
    {
    public:
        EventLoop();
        ~EventLoop();

        void exec();
        void quit();
    };
}
#endif // EVENTLOOP_H
