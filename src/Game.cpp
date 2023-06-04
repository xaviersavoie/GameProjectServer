#include <Game.hpp>
#include <TCPServer.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>

#include <typeinfo>
#include <memory>

#include <Conversions.hpp>
#include <ServerEntityPositionPacket.hpp>
#include <ClientEntityPositionPacket.hpp>

using json = nlohmann::json;

void Game::gameLoop(boost::asio::io_context *io_context, TCPServer *server)
	{

		while (true) //TODO: Incremental JSON parsing with prepending, DONT PARSE SAME PACKETS TWICE!!!
		{
                        std::cout << "Start of loop" << std::endl;
			io_context->poll();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(200));

                        std::cout << "CONNECTIONS: " << server->active_connections.size() << std::endl;

                        for (int i = 0; i < server->active_connections.size(); i++) {
                            std::cout << "lop from conn\n";
                            server->active_connections[i]->process_incoming_packets();
                            std::cout << "Queue size: " << server->active_connections[i]->incoming_packets_queue.size() << std::endl;
                        }

                        for (int i = 0; i < server->active_connections.size(); i++) {
                            std::vector<ServerEntityPositionPacket> spos_vec;
                            for (int queue_count = 0; queue_count < server->active_connections[i]->incoming_packets_queue.size(); queue_count++) {
                                std::shared_ptr<ClientEntityPositionPacket> CPOS_PACK_PTR = std::dynamic_pointer_cast<ClientEntityPositionPacket>(server->active_connections[i]->incoming_packets_queue.front()); 
                                server->active_connections[i]->incoming_packets_queue.pop();

                                ServerEntityPositionPacket outSPOS(CPOS_PACK_PTR->x, CPOS_PACK_PTR->y, CPOS_PACK_PTR->z, CPOS_PACK_PTR->entityID);
                                spos_vec.emplace_back(outSPOS);

                            }

                            for (ServerEntityPositionPacket pack : spos_vec) {
                                for (int j = 0; j < server->active_connections.size(); j++) {
                                    if (i != j) {
                                        server->active_connections[j]->outgoing_packets_queue.push(pack.serialize_packet());
                                        server->active_connections[j]->send_next_packet();
                                    }
                                }
                            }
                        }

                        for (int i = 0; i < server->active_connections.size(); i++) {
                            server->active_connections[i]->read_into_buffer();
                            server->active_connections[i]->send_next_packet();
                        }
			std::cout << "loop";
		}
    }
