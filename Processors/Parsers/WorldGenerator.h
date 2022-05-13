//
// Created by true on 2022-04-28.
//

#ifndef SSDL_WORLDGENERATOR_H
#define SSDL_WORLDGENERATOR_H
#include "../../Entities/GameObjects/World/GameWorld.h"
#include <string>
#include <fstream>
#include <sstream>

class WorldGenerator {
	static GameWorld &parseFromString(const std::string&, [[maybe_unused]] GameWorld* ptr);

public:
	static GameWorld &generateWorld(const std::string& map_filepath = "labirinth.txt");
};

#endif //SSDL_WORLDGENERATOR_H
