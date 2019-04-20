#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

//create a player
auto& player(manager.addEntity());

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char *title, int xpos, int ypos, int width, int height,
	bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
		}

		isRunning = true;
	}

	//Initialise SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		//2048 (2MB) should be fine, may have to fiddle with to avoid lag
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/proj.png");

	assets->AddSound("test_thud", "assets/332668__reitanna__big-thud2.wav");

	map = new Map("terrain", 3, 32);

	map->LoadMap("assets/map.map", 10, 10);
	
	//TODO: make a CreatePlayer() in AssetManager
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addComponent<StatusComponent>(100);
	player.addComponent<AudioComponent>();
	player.getComponent<AudioComponent>().addSound("test_thud","thud");
	player.addGroup(groupPlayers);

	//AmbientExamples
	auto& ambient(manager.addEntity());
	ambient.addComponent<TransformComponent>(0.0f, 0.0f);
	ambient.addComponent<AudioComponent>();
	ambient.getComponent<AudioComponent>().addSound("test_thud", "ambient");
	ambient.addGroup(groupAmbientSounds);

	/*//ProjectileExamples
	assets->CreateProjectile(Vector2D(60, 60), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");
	*/
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& ambient_sounds(manager.getGroup(Game::groupAmbientSounds));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:	//Generated when close button on window
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update() {

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	//Call update functions of game entities
	manager.refresh();
	manager.update();	//update all entities, which will update all our components

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			//if collided this turn, move back to the pos was in before update()
			player.getComponent<TransformComponent>().position = playerPos;
			player.getComponent<AudioComponent>().PlaySound("thud", MIX_MAX_VOLUME / 2);
			//Mix_PlayChannel(-1, assets->GetSound("test_thud"), 0);
			//std::cout << player.getComponent<StatusComponent>().health << std::endl;
		}
	}

	for (auto& a : ambient_sounds) {
		float distance = a->getComponent<TransformComponent>().getVectorTo(playerPos).length();
		if (distance < 1000) {
			std::cout << "Playing ambient: distance is " << distance << std::endl;
			//TODO add a max distance inside the audio component!
			a->getComponent<AudioComponent>().PlaySound("ambient", MIX_MAX_VOLUME, distance);
		}
	}

	for (auto& p : projectiles) {
		SDL_Rect pCol = p->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(pCol, playerCol)) {
			p->destroy();
			std::cout << "Projectile hit Player!" << std::endl;
			//TODO effect any health or whatever... (by adding type to projectile or whatever...)
		}
	}

	//Replace these with window size variables (these are halved here)
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	//limit camera movement
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) { t->draw(); }
	//remove this to hide colliders (TODO: better to have a debug key though!)
	for (auto& c : colliders) { c->draw(); } 
	for (auto& p : players) { p->draw(); }
	for (auto& p : projectiles) { p->draw(); }

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}