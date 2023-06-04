#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <ctime>
#include <string>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <TCPConnection.hpp>
#include <VoxelJohan.hpp>
#include <Chunk.hpp>
#include <WorldServer.hpp>
#include <unordered_map>
#include <Conversions.hpp>

#include <Game.hpp>


        TCPConnection::TCPConnection(boost::asio::io_context& io_context) : socket_(io_context), reading(false), writing(false) {
        }

        typedef boost::shared_ptr<TCPConnection> pointer;

        pointer TCPConnection::create(boost::asio::io_context& io_context)
        {
            return pointer(new TCPConnection(io_context));
        }

        boost::asio::ip::tcp::socket& TCPConnection::socket() {
            return socket_;
        }

        void TCPConnection::start() {

                                    
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                    std::shared_ptr<Chunk> chunkPtr = std::make_shared<Chunk>(i * 16, 0, j * 16);
                    WorldServer::loadedChunks[("x" + std::to_string(i) + "y" + std::to_string(0) + "z" + std::to_string(j))] = chunkPtr;
                    std::string chunkPack = chunkPtr->serializeChunkData();
                    outgoing_packets_queue.push(chunkPack);
                }
            }
            
        }

        void TCPConnection::send_next_packet() {
            std::cout << "send_next_packet start" << std::endl;
            if (!writing) {
                if (!outgoing_packets_queue.empty()) {
                    send_data(outgoing_packets_queue.front());
                    outgoing_packets_queue.pop();
                }
            }
        }

        void TCPConnection::send_data(std::string data) { //RAW WRITE, DO NOT USE DIRECTLY
                std::cout << data.length() << std::endl << std::endl;
                std::cout << data << std::endl << std::endl;
                writing = true;
                boost::asio::async_write(socket_, boost::asio::buffer(data), boost::bind(&TCPConnection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }

        void TCPConnection::read_into_buffer() {
            std::cout << "yea?";
            if (!reading) {
                reading = true;
                boost::asio::async_read(socket_, boost::asio::buffer(buf, 256), boost::bind(&TCPConnection::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            }
            std::cout << "yea.///";
        }

        void TCPConnection::read_from_buffer() {
        }

        void TCPConnection::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
            reading = false;
            std::cout << "Read something of size: " << bytes_transferred << std::endl;

            parser_.put_into_internal_string_stream(Conversions::char_arr_to_string(buf));

            if (bytes_transferred > 0) {
                read_into_buffer();
            }
        }

        void TCPConnection::handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) {
            std::cout << "Wrote something" << std::endl;
            writing = false;
            //send_next_packet();
        }

        void TCPConnection::process_incoming_packets() {
            Parser::packets_ptr_vec packets = parser_.get_packets_from_json_blobs(parser_.extract_json_blobs_from_internal_string_stream(parser_.last_parse_pos_));
            std::cout << "processed\n";
            for (int i = 0; i < packets.size(); i++) {
                incoming_packets_queue.push(packets[i]);
            }
        }

