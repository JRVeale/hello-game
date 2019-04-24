#include "Map.h"
#include "Game.h" //access to AddTile
#include <fstream>
#include "ECS.h"
#include "Components.h"

extern Manager manager;
//there is a manager defined somewhere else (in Game.cpp actually)

//this  func(in_vars) : member_var(in_var), member_var(in_var) etc format
//is just syntax to set each member_var to the value of in_var
Map::Map(std::string tID, int mscale, int tsize) : texID(tID),
													mapScale(mscale),
													tileSize(tsize){
	scaledSize = mscale * tsize;
}
Map::~Map() {
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY){
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	//parse the file
	//tile textures
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();	//ignore the comma
		}
	}

	mapFile.ignore();	//ignore the blank line between the parts of the map file

	//colliders
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(manager.addEntity("map_collider"));
				tcol.addComponent<ColliderComponent>("terrain",
														x * scaledSize,
														y * scaledSize,
														scaledSize);
				//square for now...
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();	//ignore the comma
			
		}
	}
	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity("map_tile"));
	tile.addComponent<TileComponent>(srcX, srcY,
										xpos, ypos,
										tileSize, mapScale,
										texID);
	tile.addGroup(Game::groupMap);
}