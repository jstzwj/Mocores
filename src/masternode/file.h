#ifndef FILE_H
#define FILE_H
#include<string>
#include"platform.h"
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
        virtual int lock(int);
        virtual int unlock(int);
        virtual int checkReservedLock(int *pResOut);
        virtual int fileControl(int op, void *pArg);
        virtual int sectorSize();
        virtual int deviceCharacteristics();
    protected:
        HANDLE pfile;
    };
    using File=WindowsFile;
#endif
}

#endif // FILE_H
