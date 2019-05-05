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
	void CreateProjectile(std::string name, Vector2D pos, Vector2D vel, int range, int speed, std::string id, Entity* owner);
	void CreateAmbientSoundEffect(std::string name, Vector2D pos, std::string asset_id, std::string local_id = "");

	//texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	/*//music management
	void AddMusic(std::string id, const char* path);
	Mix_Music* GetMusic(std::string id);*/

	//sounds management
	void AddSound(std::string id, const char* path);
	Mix_Chunk* GetSound(std::string id);


private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Mix_Music*> musics;
	std::map<std::string, Mix_Chunk*> sounds;
};