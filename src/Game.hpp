#ifndef GAME_HPP
#define GAME_HPP

#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <TCPServer.hpp>

class Game {
    public :
        static void gameLoop(boost::asio::io_context * io_context, TCPServer * server);
};

#endif
