#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <string>
#include <vector>

class Voxel {
    public :
        std::string voxelType;
        std::vector<long> getPosition();
        std::vector<long> pos;
        virtual std::string getVoxelType() = 0;
        Voxel(long inChunkPosX, long inChunkPosY, long inChunkPosZ);
        Voxel();
};

#endif
