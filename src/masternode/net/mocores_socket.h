#ifndef SOCKET_H
#define SOCKET_H
#include"../platform.h"
#include"../errcode.h"
#include"../config.h"



namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    #include <winsock2.h>
    #include<windows.h>
    class WinTcpSocket
    {
    public:
        using port_type=unsigned short;

        WinTcpSocket();
        /*
        WinTcpSocket(const WinTcpSocket & other)=delete;
        WinTcpSocket(const WinTcpSocket && other)=delete;
        WinTcpSocket &operator=(const WinTcpSocket & other)=delete;
        WinTcpSocket &operator=(const WinTcpSocket && other)=delete;
        */
        void create();
        int bind(const char *ip, port_type port);
        int listen();
        int connect(const char *ip, port_type port);
        WinTcpSocket accept();
        int recv(char *buffer, int maxlen,int flags);
        int send(const char *buffer, int maxlen,int flags);
        int close();
        bool isValid(){return socket_impl!=INVALID_SOCKET;}
    protected:
        SOCKET socket_impl;

    };

#endif
#ifdef MOCORES_OS_LINUX
    #include <unistd.h>
    #include <stdlib.h>
    #include<memory.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    class UnixTcpSocket
    {
    public:
        using port_type=unsigned short;

        UnixTcpSocket();
        void create();
        int bind(const char *ip, port_type port);
        int listen();
        int connect(const char *ip, port_type port);
        UnixTcpSocket accept();
        ssize_t recv(char *buffer, int maxlen, int flags);
        ssize_t send(const char *buffer, int maxlen, int flags);
        int close();
        bool isValid(){return socket_impl!=-1;}
    protected:
        int socket_impl;

    };

#endif
}

#endif // SOCKET_H
