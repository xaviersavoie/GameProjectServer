#ifndef CHUNK_HPP
#define CHUNK_HPP
 
#include <Voxel.hpp>
#include <vector>
#include <string>

class Chunk {
    

public :

    std::vector<std::shared_ptr<Voxel>> chunkData;

    long chunkPosX, chunkPosY, chunkPosZ;   

    //Chunk(Voxel inChunkData[4096]);
    Chunk(); //Default chunk
    Chunk(long inChunkPosX, long inChunkPosY, long inChunkPosZ);
    
    void changeVoxel(int posInChunkX, int posInChunkY, int posInChunkZ); //posInChunk is from 0 to 64

    std::string serializeChunkData();

// (up face going downwards in "sheets") 123456789 is the north side of the uppermost sheet, data is read like a book
// 123456789*******
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
// ****************
//
//First voxel to be read per chunk is the uppermost, northernmost and westernmost corner.
};


#endif
