#pragma once

#include <map>	//used to store list of textures that game has
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	//game objects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	void CreateDroppedItem(Vector2D pos, std::string id);

	//texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};