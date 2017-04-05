#ifndef MOCORES_MUTEX_H
#define MOCORES_MUTEX_H
#include<mutex>
#include"../platform.h"
namespace mocores
{

#ifdef MOCORES_OS_WINDOWS
    class mocores_windows_mutex
    {
    public:
        using native_handle_type=std::mutex::native_handle_type;
        mocores_windows_mutex():mutex_impl(){}
        mocores_windows_mutex( const mocores_windows_mutex& ) = delete;

        void lock(){mutex_impl.lock();}
        bool try_lock(){return mutex_impl.try_lock();}
        void unlock(){mutex_impl.unlock();}

        native_handle_type native_handle(){return mutex_impl.native_handle();}
    protected:
        std::mutex mutex_impl;
    };
    //using Mutex=mocores_windows_mutex;
#endif

#ifdef MOCORES_OS_LINUX
    class mocores_Unix_mutex
    {
    public:
        using native_handle_type=std::mutex::native_handle_type;
        mocores_Unix_mutex():mutex_impl(){}
        mocores_Unix_mutex( const mocores_Unix_mutex& ) = delete;

        void lock(){mutex_impl.lock();}
        bool try_lock(){return mutex_impl.try_lock();}
        void unlock(){mutex_impl.unlock();}

        native_handle_type native_handle(){return mutex_impl.native_handle();}
    protected:
        std::mutex mutex_impl;
    };
    using Mutex=mocores_Unix_mutex;
#endif


    using Mutex=std::mutex;

}


#endif // MOCORES_MUTEX_H
