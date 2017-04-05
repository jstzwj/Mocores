#ifndef THREAD_H
#define THREAD_H
#include<cstdint>
#include<thread>
#include<chrono>
#include"../platform.h"
namespace mocores
{
<<<<<<< HEAD

    class ThreadBase
    {
    public:
        using id=std::thread::id;

        ThreadBase()noexcept{}
        virtual ~ThreadBase()=0;
        template <class Fn, class... Args>
        explicit ThreadBase (Fn&&, Args&&... args){}
        ThreadBase (const ThreadBase&) = delete;
        ThreadBase& operator=( ThreadBase&& );
        ThreadBase (ThreadBase&& ) noexcept{}

        virtual bool joinable() const=0;
        //virtual mocores::ThreadBase::id get_id() const;
        //native_handle_type native_handle();
        //static unsigned hardware_concurrency();

        virtual void swap( ThreadBase& other )=0;
        virtual void detach()=0;
        virtual void join()=0;
    };
    #ifdef MOCORES_OS_WINDOWS
#include<process.h>
#include<windows.h>

    class WindowsThread:public ThreadBase
    {
    protected:
        std::thread inner_thread;
    public:
        using id=std::thread::id;

        WindowsThread()noexcept;
        virtual ~WindowsThread(){}
        template <class Fn, class... Args>
        explicit WindowsThread (Fn&& fn, Args&&... args);
        WindowsThread (const WindowsThread&) = delete;
        WindowsThread& operator=( WindowsThread&& other );
        WindowsThread(WindowsThread&& other) noexcept;

        virtual bool joinable() const;
        virtual mocores::WindowsThread::id get_id() const;

        virtual void swap(WindowsThread &other);
        virtual void detach();
        virtual void join();

    };
        using Thread=WindowsThread;
    #endif
#ifdef MOCORES_OS_LINUX


class UnixThread:public ThreadBase
{
protected:
    std::thread inner_thread;
public:
    using id=std::thread::id;

    UnixThread()noexcept;
    virtual ~UnixThread(){}
    template <class Fn, class... Args>
    explicit UnixThread (Fn&& fn, Args&&... args);
    UnixThread (const UnixThread&) = delete;
    UnixThread& operator=( UnixThread&& other );
    UnixThread(UnixThread&& other) noexcept;

    virtual bool joinable() const;
    virtual mocores::UnixThread::id get_id() const;

    virtual void swap(UnixThread &other);
    virtual void detach();
    virtual void join();

};
    using Thread=UnixThread;
#endif
=======
    using Thread=std::thread;
    namespace this_thread {
        using namespace std::this_thread;
    }
>>>>>>> 34e11fb2aa67063dd46ef3c9de5362363f1ed847
}


#endif // THREAD_H
