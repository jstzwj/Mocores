#include "mocores_thread.h"

namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    WindowsThread::WindowsThread()noexcept
        :ThreadBase(),inner_thread(){}

    WindowsThread &WindowsThread::operator=(WindowsThread &&other)
    {
        this->swap(other);
        return *this;
    }

    bool WindowsThread::joinable() const
    {
        return inner_thread.joinable();
    }

    WindowsThread::id WindowsThread::get_id() const
    {
        return inner_thread.get_id();
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

    WindowsThread::WindowsThread(WindowsThread &&other)noexcept
    {
        this->swap(other);
    }

    template <class Fn, class... Args>
    WindowsThread::WindowsThread(Fn &&fn, Args &&...args)
    {
        inner_thread=std::thread(std::forward<Fn>(fn),std::forward<Args>(args)...);
    }
#endif

}
