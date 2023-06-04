#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system.hpp>
#include <TCPConnection.hpp>

class TCPServer {
    public :
        TCPServer(boost::asio::io_context& io_context);
        void start_accept();

        std::vector<TCPConnection::pointer> active_connections;

    private :
        void handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code& error_code);

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
};    


#endif
