#include "mocores_socket.h"

namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    WinTcpSocket::WinTcpSocket()
    {

    }

    void WinTcpSocket::create()
    {
        WSADATA  Ws;

        //Init Windows Socket
        if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
        {
            //ErrCode::setErrMsg(GetLastError());
            throw MOCORES_TCPSOCKET_ERROR_INIT;
        }
        //Create Socket
        socket_impl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    int WinTcpSocket::bind(const char * ip, port_type port)
    {
        struct sockaddr_in localAddr;
        localAddr.sin_family = AF_INET;
        localAddr.sin_addr.s_addr = inet_addr(ip);
        localAddr.sin_port = htons(port);
        memset(localAddr.sin_zero, 0x00, 8);
        //Bind Socket
        return mocores::bind(this->socket_impl, (struct sockaddr*)&localAddr, sizeof(localAddr));
    }

    int WinTcpSocket::listen()
    {
        //listen
        return mocores::listen(socket_impl, MOCORES_SOCKET_LISTEN_BACKLOG);
    }

    int WinTcpSocket::connect(const char * ip,port_type port)
    {
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip);
        serverAddr.sin_port = htons(port);
        memset(serverAddr.sin_zero, 0x00, 8);
        return ::mocores::connect(this->socket_impl,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    WinTcpSocket WinTcpSocket::accept()
    {
        struct sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket;
        clientSocket = mocores::accept(this->socket_impl, (struct sockaddr*)&clientAddr, &addrLen);
        WinTcpSocket resultSocket;
        resultSocket.socket_impl=clientSocket;
        return resultSocket;
    }

    int WinTcpSocket::recv(char * buffer, int maxlen, int flags)
    {
        int ret;
        ret = mocores::recv(this->socket_impl, buffer, maxlen, 0);
        if ( ret == 0 || ret == SOCKET_ERROR )
        {
            return ret;
        }
        return ret;
    }

    int WinTcpSocket::send(const char * buffer, int maxlen, int flags)
    {
        int ret;
        ret = mocores::send(this->socket_impl, buffer, maxlen, 0);
        if ( ret == SOCKET_ERROR )
        {
            return ret;
        }
        return ret;
    }

    int WinTcpSocket::close()
    {
        int ret=closesocket(this->socket_impl);
        WSACleanup();
        return ret;
    }
#endif

#ifdef MOCORES_OS_LINUX
    UnixTcpSocket::UnixTcpSocket()
    {

    }

    void UnixTcpSocket::create()
    {
        //Create Socket
        socket_impl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    int UnixTcpSocket::bind(const char * ip, port_type port)
    {
        struct sockaddr_in localAddr;

        memset(&localAddr, 0, sizeof(localAddr));
        localAddr.sin_family = AF_INET;
        localAddr.sin_port = htons(port);

        if(inet_pton(AF_INET, ip, &localAddr.sin_addr) < 0){
            throw MOCORES_TCPSOCKET_ERROR_BIND;
        }

        //Bind Socket
        return ::mocores::bind(this->socket_impl, (struct sockaddr*)&localAddr, sizeof(localAddr));
    }

    int UnixTcpSocket::listen()
    {
        //listen
        return ::mocores::listen(socket_impl, MOCORES_SOCKET_LISTEN_BACKLOG);
    }

    int UnixTcpSocket::connect(const char * ip,port_type port)
    {
        struct sockaddr_in serverAddr;

        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);

        if(inet_pton(AF_INET, ip, &serverAddr.sin_addr) < 0){
            throw MOCORES_TCPSOCKET_ERROR_BIND;
        }
        return ::mocores::connect(this->socket_impl,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    UnixTcpSocket UnixTcpSocket::accept()
    {
        struct sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);
        int clientSocket;
        clientSocket = ::mocores::accept(this->socket_impl, (struct sockaddr*)&clientAddr, &addrLen);
        UnixTcpSocket resultSocket;
        resultSocket.socket_impl=clientSocket;
        return resultSocket;
    }

    ssize_t UnixTcpSocket::recv(char * buffer,int maxlen, int flags)
    {
        ssize_t ret;
        ret = ::mocores::recv(this->socket_impl, buffer, maxlen, flags);
        if ( ret < 0 )
        {
            return ret;
        }

        return ret;
    }

    ssize_t UnixTcpSocket::send(const char * buffer,int maxlen, int flags)
    {
        int ret;

        ret = ::mocores::send(this->socket_impl, buffer, maxlen, flags);
        if ( ret < 0 )
        {
            return ret;
        }

        return ret;
    }

    int UnixTcpSocket::close()
    {
        return ::mocores::close(this->socket_impl);
    }
#endif
}
