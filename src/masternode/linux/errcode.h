#ifndef ERRCODE_H
#define ERRCODE_H

namespace mocores
{

    enum ErrorCode
    {
        MOCORES_GOOD,
        MOCORES_FILE_ERROR_OPEN,
        MOCORES_FILE_ERROR_GETSIZE,
        MOCORES_FILE_ERROR_SEEK,
        MOCORES_IO_ERROR_READ,
        MOCORES_IO_ERROR_WRITE,
        MOCORES_FILE_ERROR_TRUNCATE,
        MOCORES_FILE_ERROR_SYNC,
        MOCORES_FILE_ERROR_LOCK,
        MOCORES_FILE_ERROR_UNLOCK
    };

    class ErrCode
    {
    public:
        ErrCode();
    };
}


#endif // ERRCODE_H
