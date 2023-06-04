#ifndef WORLD_SERVER_HPP
#define WORLD_SERVER_HPP

#include <unordered_map>
#include <Chunk.hpp>
#include <string>

class WorldServer {
    public: 
        static std::unordered_map<std::string, std::shared_ptr<Chunk>> loadedChunks;
        //static std::unordered_map<std::string, Entity> entities;

        void addChunk();
        void removeAndSaveChunk();

        void addEntity();
        void removeEntity();

};

#endif
