#include <VoxelDirt.hpp>
#include <string>
#include <iostream>

VoxelDirt::VoxelDirt(long x, long y, long z) : Voxel(x, y, z)  {

    //std::cout << "From object initialization : " << voxelType << std::endl;
}

std::string VoxelDirt::getVoxelType() {
    return voxelType;
}
