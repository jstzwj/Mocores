#ifndef SOCKET_H
#define SOCKET_H
#include"platform.h"
namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    #include <winsock2.h>
    class WinSocket
    {
    public:
        using port_type=unsigned short;

        WinSocket();
        WinSocket(const WinSocket & other)=delete;
        WinSocket(const WinSocket && other)=delete;
        WinSocket &operator=(const WinSocket & other)=delete;
        WinSocket &operator=(const WinSocket && other)=delete;
        void create();
        void bind(const char *ip, port_type port);
        void listen();
        void connect(const char *ip, port_type port);
        void accept();
        void recv();
        void send();
        void close();
    protected:
        SOCKET socket_impl;

    };

#endif

}

#endif // SOCKET_H
