#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include<string>
#include<cstdint>
#include"file.h"



namespace mocores
{
    class FileSystemBase
    {
    public:
        FileSystemBase():maxPathname(255){}
        virtual ~FileSystemBase(){}
        int maxPathname;          /* Maximum file pathname length */
        void *pAppData;          /* Pointer to application-specific data */
        virtual int open(File& file,int flags)=0;
        virtual int close(File& file)=0;
        virtual int del(const std::string & path)=0;
        virtual bool access(const std::string & path)=0;
        //int Randomness(int nByte, char *zOut);
        //int Sleep(int microseconds);
        //int CurrentTime(double*);
        //int GetLastError(int, char *);
        //int CurrentTimeInt64(int64_t*);
        //int SetSystemCall(const char *zName, sqlite3_syscall_ptr);
        //sqlite3_syscall_ptr xGetSystemCall(const char *zName);
        //const char *NextSystemCall(const char *zName);
    };
    //==========
    //系统依赖代码
    //==========
#ifdef MOCORES_OS_WINDOWS
    class WindowsFileSystem:public FileSystemBase
    {
    public:
        WindowsFileSystem():FileSystemBase(){}
        virtual ~WindowsFileSystem(){}
        virtual int open(File& file, int flags);
        virtual int close(File& file);
        virtual int del(const std::string & path);
        virtual bool access(const std::string & path);
    };
    using FileSystem=WindowsFileSystem;
#endif

}


#endif // FILESYSTEM_H
