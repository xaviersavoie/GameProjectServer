#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <string>
#include <queue>

#include <Parser.hpp>
#include <CPacket.hpp>

class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {

    public :

        TCPConnection(boost::asio::io_context& io_context);

        typedef boost::shared_ptr<TCPConnection> pointer;

        static pointer create(boost::asio::io_context& io_context);

        void send_data(std::string data);

        void read_into_buffer();

        void send_next_packet();

        bool ready;

        boost::asio::streambuf sbuf;

        std::array<char, 256> buf; 

        boost::asio::ip::tcp::socket& socket();

        void start();

        void read_from_buffer();

        std::queue<std::string> outgoing_packets_queue;

        std::queue<std::shared_ptr<CPacket>> incoming_packets_queue;

        bool reading, writing;

        void process_incoming_packets();

    private :
        void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

        void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

        boost::asio::ip::tcp::socket socket_;
        std::string message_;

        Parser parser_;


};

#endif
