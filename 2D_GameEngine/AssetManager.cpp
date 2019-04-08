#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man) {

}

AssetManager::~AssetManager() {

}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id) {
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1); //TODO more automatic size and scale
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::CreateDroppedItem(Vector2D pos, std::string id) {
	auto& testDrop(manager->addEntity());
	testDrop.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	testDrop.addComponent<SpriteComponent>(id, false);
	testDrop.addComponent<ColliderComponent>("droppedItem");
	testDrop.addGroup(Game::groupDroppedItems);
}

void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}