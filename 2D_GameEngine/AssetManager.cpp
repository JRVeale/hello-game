#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man) {

}

AssetManager::~AssetManager() {

}

void AssetManager::CreateProjectile(std::string name, Vector2D pos, Vector2D vel, int range, int speed, std::string id) {
	auto& projectile(manager->addEntity(name));
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1); //TODO more automatic size and scale
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}


void AssetManager::CreateAmbientSoundEffect(std::string name, Vector2D pos, std::string asset_id, std::string local_id ) {
	auto& ambient(manager->addEntity(name));
	ambient.addComponent<TransformComponent>(pos);
	ambient.addComponent<AudioComponent>();
	ambient.getComponent<AudioComponent>().addSoundEffect(asset_id, local_id);
	ambient.addGroup(Game::groupAmbientSounds);
}

//texture management
void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

/*//music management
void AssetManager::AddMusic(std::string id, const char* path) {
	musics.emplace(id, Mix_LoadMUS(path));
	if (musics[id] == NULL) {
		std::cout << "Failed to load music: " << path << std::endl;
	}
}

Mix_Music* AssetManager::GetMusic(std::string id) {
	return musics[id];
}*/

//sound management
void AssetManager::AddSound(std::string id, const char* path) {
	sounds.emplace(id, Mix_LoadWAV(path));
	if (sounds[id] == NULL) {
		std::cout << "Failed to load sound: " << path << std::endl;
	}
}

Mix_Chunk* AssetManager::GetSound(std::string id) {
	return sounds[id];
}