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

#ifdef MOCORES_OS_LINUX
    UnixFile::UnixFile(const std::string &path)
        :FileBase(path)
    {

    }

    int UnixFile::open(int flags)
    {
        int oflag = 0;

        if((flags&MOCORES_OPEN_CREATE)!=0)
        {
            oflag |= O_CREAT;
        }
        if((flags&MOCORES_OPEN_READONLY)!=0)
        {
            oflag|=O_RDONLY;
        }
        if((flags&MOCORES_OPEN_READWRITE)!=0)
        {
            oflag|=O_RDWR;
        }
        if((flags&MOCORES_OPEN_APPEND) != 0)
        {
            oflag|=O_APPEND;
        }

        /*! open function in fcntl.h */
        if(oflag & O_CREAT){
            pfile = ::mocores::open(filePath.c_str(), oflag, FILE_MODE);
        }else{
            pfile = ::mocores::open(filePath.c_str(), oflag);
        }

        if(pfile >= 0)
        {
            /*! unlink file if it is a temp file */
            if(flags&MOCORES_OPEN_DELETEONCLOSE)
            {
                if(unlink(filePath.c_str()) < 0){
                     return MOCORES_FILE_ERROR_OPEN;
                }
            }
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_OPEN;
        }
    }

    int UnixFile::close()
    {
        if(::mocores::close(pfile) < 0)
            return MOCORES_FILE_ERROR_CLOSE;
        return MOCORES_GOOD;
    }

    /**
     * @return number of bytes read, 0 if end of file,  -1 on error
     */
    int UnixFile::read(char * buffer, int readLen, int64_t offset)
    {
        if(::mocores::lseek(pfile, offset, SEEK_SET) < 0)
        {
            return -1;
        }

        return ::mocores::read(pfile, buffer, readLen);
    }

    /**
     * @return number of bytes write, -1 on error
     */
    int UnixFile::write(const char *buffer, int writeLen, int64_t offset)
    {
        if(::mocores::lseek(pfile, offset, SEEK_SET) < 0)
        {
            return -1;
        }

        return ::mocores::write(pfile, buffer, writeLen);
    }

    int UnixFile::truncate(int64_t size)
    {
        if(::mocores::truncate(filePath.c_str(), size) == 0)
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_TRUNCATE;
        }
    }

    int UnixFile::sync(int flags)
    {
        if(::mocores::fsync(pfile) == 0)
        {
            return MOCORES_GOOD;
        }
        else
        {
            return MOCORES_FILE_ERROR_SYNC;
        }
    }

    int UnixFile::fileSize(int64_t *pSize)
    {
        struct stat buf;

        if(::mocores::stat(filePath.c_str(), &buf) < 0){
             return MOCORES_FILE_ERROR_GETSIZE;
        }

        *pSize = buf.st_size;
        return MOCORES_GOOD;
    }

    /**
     * @note Write lock
     */
    int UnixFile::lock(int64_t offset, int64_t len)
    {
        struct flock lk;

        lk.l_type = F_WRLCK;
        lk.l_whence = SEEK_SET;
        lk.l_start = offset;
        lk.l_len = len;

        if(fcntl(pfile, F_SETLK, &lk) < 0)
        {
            return MOCORES_FILE_ERROR_LOCK;
        }
        else
        {
            return MOCORES_GOOD;
        }
    }

    int UnixFile::unlock(int64_t offset, int64_t len)
    {
        struct flock lk;

        lk.l_type = F_UNLCK;
        lk.l_whence = SEEK_SET;
        lk.l_start = offset;
        lk.l_len = len;
        if(fcntl(pfile, F_SETLK, &lk) < 0)
        {
            return MOCORES_FILE_ERROR_UNLOCK;
        }
        else
        {
            return MOCORES_GOOD;
        }
    }

    int UnixFile::checkReservedLock(int *pResOut)
    {
        return MOCORES_GOOD;
    }

    int UnixFile::fileControl(int op, void *pArg)
    {
        return MOCORES_GOOD;
    }

    int UnixFile::sectorSize()
    {
        return MOCORES_GOOD;
    }

    int UnixFile::deviceCharacteristics()
    {
        return MOCORES_GOOD;
    }
#endif

}
