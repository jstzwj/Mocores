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
        HANDLE pfile=CreateFile((LPCWSTR)path.c_str(),
                   GENERIC_READ,
                   0,
                   NULL,
                   OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL,
                   NULL);
        if(INVALID_HANDLE_VALUE!=pfile)
        {
            CloseHandle(pfile);
            return true;
        }
        else
        {
            return false;
        }
    }

#endif

}
