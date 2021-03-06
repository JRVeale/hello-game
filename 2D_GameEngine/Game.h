#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height,
				bool fullscreen);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();	//Memory management...

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders,
		groupAmbientSounds,
		groupProjectiles
	};

private:
	int count = 0;
	SDL_Window *window;
};