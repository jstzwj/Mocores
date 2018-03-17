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
#ifdef MOCORES_OS_LINUX
    UnixThread::UnixThread()noexcept
        :ThreadBase(),inner_thread(){}

    UnixThread &UnixThread::operator=(UnixThread &&other)
    {
        this->swap(other);
        return *this;
    }

    bool UnixThread::joinable() const
    {
        return inner_thread.joinable();
    }
=======
>>>>>>> 34e11fb2aa67063dd46ef3c9de5362363f1ed847

    UnixThread::id UnixThread::get_id() const
    {
        return inner_thread.get_id();
    }

    void UnixThread::swap(UnixThread &other)
    {
        std::thread tmp=std::move(other.inner_thread);
        other.inner_thread=std::move(this->inner_thread);
        this->inner_thread=std::move(tmp);
    }

    void UnixThread::detach()
    {
        inner_thread.detach();
    }

    void UnixThread::join()
    {
        inner_thread.join();
    }

    UnixThread::UnixThread(UnixThread &&other)noexcept
    {
        this->swap(other);
    }

    template <class Fn, class... Args>
    UnixThread::UnixThread(Fn &&fn, Args &&...args)
    {
        inner_thread=std::thread(std::forward<Fn>(fn),std::forward<Args>(args)...);
    }
#endif
}
