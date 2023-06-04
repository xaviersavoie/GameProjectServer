#ifndef VOXEL_AIR_HPP
#define VOXEL_AIR_HPP

#include <Voxel.hpp>

class VoxelAir: public Voxel {
    
    public:

        VoxelAir(long x, long y, long z);
        std::string getVoxelType();
        std::string voxelType = "voxel-air"; 

};

#endif
