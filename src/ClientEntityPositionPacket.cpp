#include <ClientEntityPositionPacket.hpp>
#include <vector>

ClientEntityPositionPacket::ClientEntityPositionPacket(std::vector<double> pos, long inEntityID) : x(pos[0]), y(pos[1]), z(pos[2]), entityID(inEntityID) {}
