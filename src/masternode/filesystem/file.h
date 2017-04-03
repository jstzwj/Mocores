#ifndef FILE_H
#define FILE_H
#include<string>
#include"../platform.h"
#include"iomethod.h"
#include"errcode.h"


namespace mocores
{
    class FileBase:public IoMethod
    {
    public:
        FileBase(const std::string & path);
        virtual ~FileBase(){}
    protected:
        std::string filePath;
    };
    //==========
    //系统依赖代码
    //==========
#ifdef MOCORES_OS_WINDOWS
    #include<windows.h>
    class WindowsFile:public FileBase
    {
    public:
        WindowsFile(const std::string & path);
        virtual ~WindowsFile(){}
        virtual int open(int flags);
        virtual int close();
        virtual int read(char *buffer, int readLen, int64_t offset);
        virtual int write(const char *buffer, int writeLen, int64_t offset);
        virtual int truncate(int64_t size);
        virtual int sync(int flags);
        virtual int fileSize(int64_t *pSize);
        virtual int lock(int64_t offset, int64_t len);
        virtual int unlock(int64_t offset, int64_t len);
        virtual int checkReservedLock(int *pResOut);
        virtual int fileControl(int op, void *pArg);
        virtual int sectorSize();
        virtual int deviceCharacteristics();
    protected:
        HANDLE pfile;
    };
    using File=WindowsFile;
#endif
#ifdef MOCORES_OS_LINUX

    /*! off_t => off64_t */
    #define _FILE_OFFSET_BITS 64

    #include<unistd.h>
    #include<fcntl.h>
    #include<sys/stat.h>
    #include<sys/socket.h>
    #define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
    /**
     * @brief File descriptor in Unix
     * @author cheniison
     * @date 2017-03-31 16:30:00
     */
    class UnixFile:public FileBase
    {
    public:
        UnixFile(const std::string & path);
        virtual ~UnixFile(){}
        virtual int open(int flags);
        virtual int close();
        virtual int read(char *buffer, int readLen, int64_t offset);
        virtual int write(const char *buffer, int writeLen, int64_t offset);
        virtual int truncate(int64_t size);
        virtual int sync(int flags);
        virtual int fileSize(int64_t *pSize);
        virtual int lock(int64_t offset, int64_t len);
        virtual int unlock(int64_t offset, int64_t len);
        virtual int checkReservedLock(int *pResOut);
        virtual int fileControl(int op, void *pArg);
        virtual int sectorSize();
        virtual int deviceCharacteristics();
    protected:
        int pfile;
    };
    using File=UnixFile;
#endif
}



#endif // FILE_H
