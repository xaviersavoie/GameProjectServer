#ifndef VOXEL_DIRT_HPP
#define VOXEL_DIRT_HPP

#include <Voxel.hpp>

class VoxelDirt: public Voxel {
    
    public:

        VoxelDirt(long x, long y, long z);
        std::string getVoxelType();
        std::string voxelType = "voxel-dirt"; 

};

#endif
