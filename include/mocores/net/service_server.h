#ifndef MOCORES_COMMON_NET_SERVICE_SERVER_H
#define MOCORES_COMMON_NET_SERVICE_SERVER_H

#include <boost/asio.hpp>

namespace mocores
{
    class ServiceServer
    {
    public:
        ServiceServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint)
            : acceptor_(io_context, endpoint)
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec)
                {
                    std::make_shared<chat_session>(std::move(socket), room_)->start();
                }

                do_accept();
            });
        }

        tcp::acceptor acceptor_;
        chat_room room_;
    };
}

#endif