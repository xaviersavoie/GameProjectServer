#ifndef VOXEL_JOHAN_HPP
#define VOXEL_JOHAN_HPP

#include <Voxel.hpp>

class VoxelJohan: public Voxel {
    
    public:

        VoxelJohan(long x, long y, long z);
        std::string getVoxelType();
        std::string voxelType = "voxel-johan"; 

};

#endif
