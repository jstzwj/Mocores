#ifndef ERRCODE_H
#define ERRCODE_H
#include<string>
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
        MOCORES_FILE_ERROR_UNLOCK,

        MOCORES_TCPSOCKET_ERROR_INIT,
        MOCORES_TCPSOCKET_ERROR_CREATE,
        MOCORES_TCPSOCKET_ERROR_BIND,
        MOCORES_TCPSOCKET_ERROR_LISTEN,
        MOCORES_TCPSOCKET_ERROR_ACCEPT,
        MOCORES_TCPSOCKET_ERROR_RECV,
        MOCORES_TCPSOCKET_ERROR_SEND,

        MOCORES_SQL_ERROR_CONNECTION_NOT_INIT,

        MOCORES_VARIANT_EMPTY
    };

    class ErrCode
    {
    public:
        ErrCode();
        static void setErrMsg(const std::string & str);
        static std::string getErrMsg();
    private:
        static std::string errmsg;
    };
}


#endif // ERRCODE_H
