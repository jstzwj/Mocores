#include "file.h"

namespace mocores
{
    FileBase::FileBase(const std::string &path)
        :IoMethod(),filePath(path)
    {

    }

#ifdef MOCORES_OS_WINDOWS
    WindowsFile::WindowsFile(const std::string &path)
        :FileBase(path)
    {

    }
    /*!
     * \brief WindowsFile::open
     * \param flags File io flag
     * \return error code
     * \note Default mode is OPEN_EXISTING 文件必须已经存在。否则返回错误。
     */
    int WindowsFile::open(int flags)
    {
        //MessageBox(NULL, L"打开文件失败", L"Error", MB_OK);
        DWORD dwDesiredAccess=0;
        DWORD dwCreationDisposition=OPEN_EXISTING;
        DWORD dwFlagsAndAttributes=FILE_ATTRIBUTE_NORMAL;
        if((flags&MOCORES_OPEN_CREATE)!=0)
        {
            dwCreationDisposition=CREATE_NEW;
        }
        if((flags&MOCORES_OPEN_READONLY)!=0)
        {
            dwDesiredAccess|=GENERIC_READ;
        }
        if((flags&MOCORES_OPEN_READWRITE)!=0)
        {
            dwDesiredAccess|=(GENERIC_WRITE|GENERIC_READ);
        }
        if((flags&MOCORES_OPEN_DELETEONCLOSE)!=0)
        {
            dwFlagsAndAttributes|=FILE_FLAG_DELETE_ON_CLOSE;
        }
        pfile = CreateFileA(filePath.c_str(), dwDesiredAccess, 0, NULL, dwCreationDisposition,
                dwFlagsAndAttributes, NULL);
        if(pfile!=INVALID_HANDLE_VALUE)
        {
            return MOCORES_GOOD;
        }
        else
        {
            CloseHandle(pfile);
            return MOCORES_FILE_ERROR_OPEN;
        }
    }

    int WindowsFile::close()
    {
        CloseHandle(pfile);
        return MOCORES_GOOD;
    }

    int WindowsFile::read(char * buffer, int readLen, int64_t offset)
    {
        DWORD bytesRead;
        if(!SetFilePointerEx(pfile,*(LARGE_INTEGER *)(&offset),NULL,FILE_BEGIN))
        {
            return MOCORES_FILE_ERROR_SEEK;
        }
        if(!ReadFile(pfile, buffer, readLen, &bytesRead, NULL))
        {
            return MOCORES_IO_ERROR_READ;
        }
        return MOCORES_GOOD;
    }

    int WindowsFile::write(const char *buffer, int writeLen, int64_t offset)
    {
        DWORD bytesWritten;
        if(!SetFilePointerEx(pfile,*(LARGE_INTEGER *)(&offset),NULL,FILE_BEGIN))
        {
            return MOCORES_FILE_ERROR_SEEK;
        }
        if(!WriteFile(pfile,buffer,writeLen,&bytesWritten,NULL))
        {
            return MOCORES_IO_ERROR_WRITE;
        }
        return MOCORES_GOOD;
    }

    int WindowsFile::truncate(int64_t size)
    {
        if(!SetFilePointerEx(pfile,*(LARGE_INTEGER *)(&size),NULL,FILE_BEGIN))
        {
            return MOCORES_FILE_ERROR_SEEK;
        }
        if(SetEndOfFile(pfile))
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_TRUNCATE;
        }
    }

    int WindowsFile::sync(int flags)
    {
        if(FlushFileBuffers(pfile))
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_SYNC;
        }
    }

    int WindowsFile::fileSize(int64_t *pSize)
    {
        if(GetFileSizeEx(pfile,(LARGE_INTEGER *)pSize))
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_GETSIZE;
        }
    }

    int WindowsFile::lock(int)
    {
        LARGE_INTEGER file_size;
        fileSize(&file_size.QuadPart);
        if(LockFile(pfile,0,0,file_size.LowPart,file_size.HighPart))
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_LOCK;
        }
    }

    int WindowsFile::unlock(int)
    {
        LARGE_INTEGER file_size;
        fileSize(&file_size.QuadPart);
        if(UnlockFile(pfile,0,0,file_size.LowPart,file_size.HighPart))
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_UNLOCK;
        }
    }

    int WindowsFile::checkReservedLock(int *pResOut)
    {
        return MOCORES_GOOD;
    }

    int WindowsFile::fileControl(int op, void *pArg)
    {
        return MOCORES_GOOD;
    }

    int WindowsFile::sectorSize()
    {
        return MOCORES_GOOD;
    }

    int WindowsFile::deviceCharacteristics()
    {
        return MOCORES_GOOD;
    }
#endif

}
