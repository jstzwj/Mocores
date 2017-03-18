#ifndef SOCKET_H
#define SOCKET_H
#include"platform.h"
#include"errcode.h"




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
        void bind(const char *ip, port_type port);
        void listen();
        void connect(const char *ip, port_type port);
        WinTcpSocket accept();
        void recv(char *buffer, int maxlen);
        void send(const char *buffer, int maxlen);
        void close();
    protected:
        SOCKET socket_impl;

    };

#endif

}

#endif // SOCKET_H
