#ifndef MOCORES_COMMON_NET_SERVICE_SERVER_H
#define MOCORES_COMMON_NET_SERVICE_SERVER_H

#include <memory>

#include <boost/asio.hpp>

#include <mocores/net/service_session.h>

namespace mocores
{
    class ServiceServer
    {
    public:
        ServiceServer(boost::asio::io_context& io_context, const boost::asio::ip::tcp::endpoint& endpoint)
            : acceptor_(io_context, endpoint)
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if (!ec)
                {
                    std::make_shared<ServiceSession>(std::move(socket))->start();
                }

                do_accept();
            });
        }

        boost::asio::ip::tcp::acceptor acceptor_;
    };
}

#endif