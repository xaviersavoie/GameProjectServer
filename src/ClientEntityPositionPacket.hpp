#ifndef CLIENT_ENTITY_POSITION_PACKET_HPP
#define CLIENT_ENTITY_POSITION_PACKET_HPP

#include <CPacket.hpp>
#include <vector>

class ClientEntityPositionPacket : public CPacket {
    
    public:

        ClientEntityPositionPacket(std::vector<double> pos, long inEntityID);

        double x, y, z;
        long entityID;
};

#endif
