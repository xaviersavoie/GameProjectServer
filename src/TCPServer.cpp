#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system.hpp>
#include <boost/system/error_code.hpp>
#include <TCPServer.hpp>
#include <iostream>

#include <Game.hpp>

#include <TCPConnection.hpp>

        using namespace boost::asio::ip;
        using namespace boost::system;

        TCPServer::TCPServer(boost::asio::io_context& io_context) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 25569)) {
            start_accept();
            std::cout << "created tcpserver" << std::endl;
        }
        void TCPServer::start_accept() {
            std::cout << "Start accept" << std::endl;
            TCPConnection::pointer new_connection =
                TCPConnection::create(io_context_);

            acceptor_.async_accept(new_connection->socket(), boost::bind(&TCPServer::handle_accept, this, new_connection, boost::asio::placeholders::error ));
            std::cout << "After async_accept" << std::endl;
        }
        void TCPServer::handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code & error) {
            if (!error)
            {
                new_connection->start();
                active_connections.push_back(new_connection);
            }
            
            start_accept();
        }

