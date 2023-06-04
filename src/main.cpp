#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/bind/bind.hpp>
#include <TCPServer.hpp>
#include <Game.hpp>
#include <Perlin3D.hpp>
#include <fstream>
#include <Parser.hpp>
#include <ClientEntityPositionPacket.hpp>

#include <stdio.h>

#include <nlohmann/json.hpp>

#include <string>
#include <vector>


using json = nlohmann::json;

int main() {

    Game game;

    Parser parser;
    /*
    auto str = R"(
    {"packetType": "ClientEntityPosition", "position": [4, 3, 5], "entityID": 54}{"packetType": "ClientEntityPosition", "position": [2, 895, 2], "entityID": 2}{"packetType": "Clien
  )";
    auto str2 = R"(tEntityPosition", "position": [69, 69, 69], "entityID": 420})";
    parser.put_into_internal_string_stream(str);
    int last = 0;
    std::vector<json> test = parser.extract_json_blobs_from_internal_string_stream(last);
    std::cout << "blobs vec size: " << test.size() << std::endl;
    std::cout << "contents of stringstream after json blob parsing: " << parser.ss_.str() << std::endl;
    std::cout <<  "first: " << test.at(0).dump();
    std::cout <<  "second: " << test.at(1).dump();
    long testFirst = test.at(0)["entityID"].get<long>();
    long testSecond = test.at(1)["entityID"].get<long>();
    std::cout << "FIRST: " << testFirst << std::endl;
    std::cout << "SECOND: " << testSecond << std::endl;

    Parser::packets_ptr_vec fun_vec = parser.get_packets_from_json_blobs(test);

    std::cout << "Packets amount: " << fun_vec.size() << std::endl;

    std::shared_ptr<ClientEntityPositionPacket> packet = std::dynamic_pointer_cast<ClientEntityPositionPacket>(fun_vec[0]); // Example cast, I guess
    
    std::cout << "X value of first packet: " << packet->x << std::endl;
    std::cout << "Y value of first packet: " << packet->y << std::endl;
    std::cout << "Z value of first packet: " << packet->z << std::endl;
    std::cout << "ENTITY ID of first packet: " << packet->entityID << std::endl;
    */
    try {
        boost::asio::io_context io_context;
        TCPServer server(io_context);
        boost::thread t(boost::bind(&Game::gameLoop, &io_context, &server));
        t.join();
        io_context.run();
        std::cout << "ya" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
    
}
