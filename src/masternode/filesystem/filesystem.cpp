#include "filesystem.h"

namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    int WindowsFileSystem::open(File & file, int flags)
    {
        return file.open(flags);
    }

    int WindowsFileSystem::close(File & file)
    {
        return file.close();
    }

    int WindowsFileSystem::del(const std::string & path)
    {
        DeleteFile((LPCWSTR)path.c_str());
        return 0;
    }

    bool WindowsFileSystem::access(const std::string &path)
    {
        if(INVALID_HANDLE_VALUE!=
                CreateFile((LPCWSTR)path.c_str(),
                           GENERIC_READ,
                           0,
                           NULL,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL)
                )
            return true;
        else
            return false;
    }

#endif
#ifdef MOCORES_OS_LINUX
    int UnixFileSystem::open(File & file, int flags)
    {
        return file.open(flags);
    }

    int UnixFileSystem::close(File & file)
    {
        return file.close();
    }

    /**
     * @brief UnixFileSystem::del
     * @param path
     * @return 0 on success, -1 on error
     */
    int UnixFileSystem::del(const std::string & path)
    {
        return std::remove(path.c_str());
    }

    bool UnixFileSystem::access(const std::string &path)
    {
        if(::mocores::open(path.c_str(), O_RDONLY) < 0)
            return false;
        else
            return true;
    }

#endif

}
