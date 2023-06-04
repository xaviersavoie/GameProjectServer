#include <Voxel.hpp>

std::vector<long> Voxel::getPosition(){
    return pos;
}

Voxel::Voxel() {}

Voxel::Voxel(long inChunkPosX, long inChunkPosY, long inChunkPosZ) {
    pos.push_back(inChunkPosX);    
    pos.push_back(inChunkPosY);    
    pos.push_back(inChunkPosZ);    
}
