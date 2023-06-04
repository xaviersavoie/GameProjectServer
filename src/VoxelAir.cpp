#include <VoxelAir.hpp>
#include <string>
#include <iostream>

VoxelAir::VoxelAir(long x, long y, long z) : Voxel(x, y, z)  {

    //std::cout << "From object initialization : " << voxelType << std::endl;
}

std::string VoxelAir::getVoxelType() {
    return voxelType;
}
