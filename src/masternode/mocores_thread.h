#ifndef THREAD_H
#define THREAD_H
#include<cstdint>
#include"platform.h"
namespace mocores
{

    class ThreadBase
    {
    public:
        using id=uint32_t;

        ThreadBase()noexcept{}
        virtual ~ThreadBase()=0;
        template <class Fn, class... Args>
        explicit ThreadBase (Fn&& fn, Args&&... args){}
        ThreadBase (const ThreadBase&) = delete;
        ThreadBase& operator=( ThreadBase&& other );
        ThreadBase (ThreadBase&& x) noexcept{}

        virtual bool joinable() const=0;
        virtual mocores::ThreadBase::id get_id() const=0;
        //native_handle_type native_handle();
        //static unsigned hardware_concurrency();

        virtual void swap( ThreadBase& other )=0;
        virtual void detach()=0;
        virtual void join()=0;
    };
    #ifdef MOCORES_OS_WINDOWS
    class WindowsThread:public ThreadBase
    {
    public:
        using id=uint32_t;

        WindowsThread()noexcept{}
        virtual ~WindowsThread()=0;
        template <class Fn, class... Args>
        explicit WindowsThread (Fn&& fn, Args&&... args){}
        WindowsThread (const WindowsThread&) = delete;
        WindowsThread& operator=( WindowsThread&& other );
        WindowsThread (WindowsThread&& x) noexcept{}

        virtual bool joinable() const=0;
        virtual mocores::WindowsThread::id get_id() const=0;
        //native_handle_type native_handle();
        //static unsigned hardware_concurrency();

        virtual void swap( WindowsThread& other )=0;
        virtual void detach()=0;
        virtual void join()=0;
    };
        using Thread=WindowsThread;
    #endif

}


#endif // THREAD_H
