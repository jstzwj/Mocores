#include "mocores_thread.h"

namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    WindowsThread::WindowsThread()
        :Thread(),inner_thread(){}

    WindowsThread::~WindowsThread(){}

    WindowsThread &WindowsThread::operator=(WindowsThread &&other)
    {
        this->swap(std::move(other));
    }

    bool WindowsThread::joinable() const
    {
        return inner_thread.joinable();
    }

    WindowsThread::id WindowsThread::get_id() const
    {
        return inner_thread.id;
    }

    void WindowsThread::swap(WindowsThread &other)
    {
        std::thread tmp=std::move(other.inner_thread);
        other.inner_thread=std::move(this->inner_thread);
        this->inner_thread=std::move(tmp);
    }

    void WindowsThread::detach()
    {
        inner_thread.detach();
    }

    void WindowsThread::join()
    {
        inner_thread.join();
    }

    WindowsThread::WindowsThread(WindowsThread &&other)
    {
        this->swap(std::move(other));
    }

    template <class Fn, class... Args>
    WindowsThread::WindowsThread(Fn &&fn, Args &&...args)
    {
        inner_thread=std::thread(std::forward<Fn>(fn),std::forward<Args>(args...));
    }
#endif

}
