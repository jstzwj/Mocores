/*
    © 2016-2017 mocores
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
*/
/*!
\file errcode.h
\ingroup main
\brief
\version b0001
\author WangJun <1103870790@qq.com>
\since b0001
\par created time:
    2017-03-30 11:28:38 +0800
\par modified time:
    2017-03-30 11:28:38 +0800
\par text encoding:
    UTF-8
\par module name:
    mocores::ErrCode
\see
*/
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
        MOCORES_FILE_ERROR_CLOSE,

        MOCORES_TCPSOCKET_ERROR_INIT,
        MOCORES_TCPSOCKET_ERROR_CREATE,
        MOCORES_TCPSOCKET_ERROR_BIND,
        MOCORES_TCPSOCKET_ERROR_LISTEN,
        MOCORES_TCPSOCKET_ERROR_CONNECT,
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
