#ifndef MOCORES_NET_SERVICE_CLIENT_H
#define MOCORES_NET_SERVICE_CLIENT_H

#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <list>
#include <iostream>
#include <thread>

#include <mocores/net/protocol/service_message.h>

using boost::asio::ip::tcp;

namespace mocores
{
    class chat_client
    {
    public:
        chat_client(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints)
            : io_context_(io_context), socket_(io_context)
        {
            do_connect(endpoints);
        }

        void write(const ServiceMessage& msg)
        {
            boost::asio::post(io_context_, [this, msg]() {
                bool write_in_progress = !write_msgs_.empty();
                write_msgs_.push_back(msg);
                if (!write_in_progress)
                {
                    do_write();
                }
            });
        }

        void close()
        {
            boost::asio::post(io_context_, [this]() { socket_.close(); });
        }

    private:
        void do_connect(const tcp::resolver::results_type& endpoints)
        {
            boost::asio::async_connect(socket_, endpoints, [this](boost::system::error_code ec, tcp::endpoint) {
                if (!ec)
                {
                    do_read_header();
                }
            });
        }

        void do_read_header()
        {
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.data(), ServiceMessage::header_length),
                                    [this](boost::system::error_code ec, std::size_t /*length*/) {
                                        if (!ec && read_msg_.decode_header())
                                        {
                                            do_read_body();
                                        }
                                        else
                                        {
                                            socket_.close();
                                        }
                                    });
        }

        void do_read_body()
        {
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                                    [this](boost::system::error_code ec, std::size_t /*length*/) {
                                        if (!ec)
                                        {
                                            std::cout.write(read_msg_.body(), read_msg_.body_length());
                                            std::cout << "\n";
                                            do_read_header();
                                        }
                                        else
                                        {
                                            socket_.close();
                                        }
                                    });
        }

        void do_write()
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                                     [this](boost::system::error_code ec, std::size_t /*length*/) {
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
                                             socket_.close();
                                         }
                                     });
        }

    private:
        boost::asio::io_context& io_context_;
        tcp::socket socket_;
        ServiceMessage read_msg_;
        std::list<ServiceMessage> write_msgs_;
    };
}

#endif