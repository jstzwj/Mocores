#ifndef IOMETHOD_H
#define IOMETHOD_H
#include<cstdint>
namespace mocores
{
    class IoMethod
    {
    public:
        IoMethod()=default;
        virtual ~IoMethod(){}
        virtual int open(int flags)=0;
        virtual int close()=0;
        virtual int read(char *buffer, int readLen, int64_t offset)=0;
        virtual int write(const char *buffer, int writeLen, int64_t offset)=0;
        virtual int truncate(int64_t size)=0;
        virtual int sync(int flags)=0;
        virtual int fileSize(int64_t *pSize)=0;
        virtual int lock(int64_t offset, int64_t len)=0;
        virtual int unlock(int64_t offset, int64_t len)=0;
        virtual int checkReservedLock(int *pResOut)=0;
        virtual int fileControl(int op, void *pArg)=0;
        virtual int sectorSize()=0;
        virtual int deviceCharacteristics()=0;
    };


}


#endif // IOMETHOD_H
