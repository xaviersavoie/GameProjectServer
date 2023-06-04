#include <Voxel.hpp>
#include <Chunk.hpp>
#include <VoxelJohan.hpp>
#include <VoxelAir.hpp>
#include <VoxelDirt.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <vector>
#include <Perlin3D.hpp>

    Chunk::Chunk(long inChunkPosX, long inChunkPosY, long inChunkPosZ) {

        double noiseArr[16][16];
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			noiseArr[i][j] = Perlin3D::generatePerlin((i + inChunkPosX) * 0.06, 16 * 0.06, (j + inChunkPosZ) * 0.06);
			
			//std::cout << noiseArr[i][j] << '\t';
		}

		//std::cout << '\n';
	}



        int count = 0;
        chunkPosX = inChunkPosX;
        chunkPosY = inChunkPosY;
        chunkPosZ = inChunkPosZ;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                for (int k = 0; k < 16; k++) {
                    std::shared_ptr<Voxel> voxelPtr;
                    if (j == 15) {
                        voxelPtr = std::make_shared<VoxelDirt>(i, ((noiseArr[i][k] + 2) * 12), k);
                        
                        chunkData.emplace_back(voxelPtr);
                        count++;
                    } else {
                        //voxelPtr = std::make_shared<VoxelAir>(i, j, k);
                    }


                }
            }
        }
    }



    void Chunk::changeVoxel(int chunkPosX, int chunkPosY, int chunkPosZ) {
        
    }

    std::string Chunk::serializeChunkData() {
        using namespace boost::json;
        array voxelsList;
        object outJson;
        outJson["packetType"] = "ServerPacketChunkData";
        for (int i = 0; i < (chunkData.size() - 1); i++) {
            object voxel;
            voxel["voxel-type"] = chunkData[i]->getVoxelType();
            std::vector<long> posVec = chunkData[i]->getPosition();
            array posArr = {posVec[0], posVec[1], posVec[2]};
            voxel["position"] = posArr;
            voxelsList.emplace_back(voxel);
        }
        outJson["voxelData"] = voxelsList;
        array chunkPos = {chunkPosX, chunkPosY, chunkPosZ};
        outJson["chunkPos"] = chunkPos;
        std::string rawJSON = serialize(outJson);

        /*
         * If ever I end up using length prefix
         *
        int len = rawJSON.length();
        std::string stringLength = to_string(len);

        std::string outString = stringLength + rawJSON;
        */

        return rawJSON;
    }
