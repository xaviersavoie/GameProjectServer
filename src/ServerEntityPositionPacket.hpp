#ifndef SERVER_ENTITY_POSITION_PACKET
#define SERVER_ENTITY_POSITION_PACKET

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ServerEntityPositionPacket {
    public:
    double x, y, z;
    long entityID;
    ServerEntityPositionPacket(double inX, double inY, double inZ, long inEntityID) : x(inX), y(inY), z(inZ), entityID(inEntityID){}

    std::string serialize_packet() {
        json j;
        j["packetType"] = "ServerEntityPositionPacket";
        j["pos"] = {x, y, z};
        j["entityID"] = entityID;

        return j.dump();
    }
};

#endif
