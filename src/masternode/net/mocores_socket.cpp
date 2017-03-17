#include "mocores_socket.h"

namespace mocores
{
#ifdef MOCORES_OS_WINDOWS
    WinSocket::WinSocket()
    {

    }

    void WinSocket::create()
    {
        WSADATA  Ws;

        //Init Windows Socket
        if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
        {
            //cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
            return -1;
        }
        //Create Socket
        socket_impl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if ( socket_impl == INVALID_SOCKET )
        {
            //cout<<"Create Socket Failed::"<<GetLastError()<<endl;
            return -1;
        }

    }

    void WinSocket::bind(const char * ip, port_type port)
    {
        struct sockaddr_in localAddr;
        int ret;
        localAddr.sin_family = AF_INET;
        localAddr.sin_addr.s_addr = inet_addr(ip);
        localAddr.sin_port = htons(port);
        memset(localAddr.sin_zero, 0x00, 8);
        //Bind Socket
        ret = ::bind(this->socket_impl, (struct sockaddr*)&localAddr, sizeof(localAddr));
        if ( ret != 0 )
        {
            cout<<"Bind Socket Failed::"<<GetLastError()<<endl;
            return -1;
        }
    }

    void WinSocket::listen()
    {
        int ret;
        //listen
        ret = ::listen(socket_impl, 10);
        if ( ret != 0 )
        {
            //cout<<"listen Socket Failed::"<<GetLastError()<<endl;
            return -1;
        }
    }

    void WinSocket::connect(const char * ip,port_type port)
    {
        struct sockaddr_in serverAddr;
        int ret;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip);
        serverAddr.sin_port = htons(port);
        memset(serverAddr.sin_zero, 0x00, 8);

        ret = ::connect(this->socket_impl,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    void WinSocket::accept()
    {
        AddrLen = sizeof(ClientAddr);
        ClientSocket = ::accept(ServerSocket, (struct sockaddr*)&ClientAddr, &AddrLen);
        if ( ClientSocket == INVALID_SOCKET )
        {
            cout<<"Accept Failed::"<<GetLastError()<<endl;
            break;
        }
    }

    void WinSocket::recv()
    {
        int ret;
        ret = ::recv(this->socket_impl, RecvBuffer, MAX_PATH, 0);
        if ( Ret == 0 || Ret == SOCKET_ERROR )
        {
            //cout<<"客户端退出!"<<endl;
            break;
        }
    }

    void WinSocket::send()
    {
        int ret;
        ret = ::send(ClientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
        if ( ret == SOCKET_ERROR )
        {
            //cout<<"Send Info Error::"<<GetLastError()<<endl;
            break;
        }

    }

    void WinSocket::close()
    {
        closesocket(this->socket_impl);
        WSACleanup();
    }
#endif
}
