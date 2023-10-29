#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class Game {

public:
	Game();
	~Game();

	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };

	static SDL_Renderer* Renderer;
	static SDL_Event event;
	static SDL_Rect camera;

	enum groupLabels : std::size_t {

		groupMap,
		groupPlayers,
		groupColliders,
		groupObjects,
		groupObjectives
	};

private:
	bool isRunning;

	SDL_Window* Window;
};