#include <VoxelJohan.hpp>
#include <string>
#include <iostream>

VoxelJohan::VoxelJohan(long x, long y, long z) : Voxel(x, y, z)  {

    //std::cout << "From object initialization : " << voxelType << std::endl;
}

std::string VoxelJohan::getVoxelType() {
    return voxelType;
}
