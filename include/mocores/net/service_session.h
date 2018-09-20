#ifndef MOCORES_NET_SERVICE_SESSION_H
#define MOCORES_NET_SERVICE_SESSION_H

#include <memory>
#include <list>

#include <boost/asio.hpp>

#include<mocores/net/protocol/message.h>

namespace mocores
{
    class ServiceSession : public std::enable_shared_from_this<ServiceSession>
    {
    public:
        ServiceSession(boost::asio::ip::tcp::socket socket)
            : socket_(std::move(socket))
        {
        }

        void start()
        {
            do_read_header();
        }

        void deliver(const Message& msg)
        {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);
            if (!write_in_progress)
            {
                do_write();
            }
        }

    private:
        void do_read_header()
        {
            auto self(shared_from_this());
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.data(), Message::header_length),
                                    [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                        if (!ec && read_msg_.decode_header())
                                        {
                                            do_read_body();
                                        }
                                        else
                                        {
                                            // room_.leave(shared_from_this());
                                        }
                                    });
        }

        void do_read_body()
        {
            auto self(shared_from_this());
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                                    [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                        if (!ec)
                                        {
                                            // room_.deliver(read_msg_);
                                            do_read_header();
                                        }
                                        else
                                        {
                                            // room_.leave(shared_from_this());
                                        }
                                    });
        }

        void do_write()
        {
            auto self(shared_from_this());
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                                     [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                         if (!ec)
                                         {
                                             write_msgs_.pop_front();
                                             if (!write_msgs_.empty())
                                             {
                                                 do_write();
                                             }
                                         }
                                         else
                                         {
                                             // room_.leave(shared_from_this());
                                         }
                                     });
        }

        boost::asio::ip::tcp::socket socket_;
        Message read_msg_;
        std::list<Message> write_msgs_;
    };
}

#endif