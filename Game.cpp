#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::Renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,800,640 };

auto& Player(manager.addEntity());
auto& Object(manager.addEntity());

int counter = 0;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialised!" << std::endl;

		Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (Window)
			std::cout << "Window initialised!" << std::endl;

		Renderer = SDL_CreateRenderer(Window, -1, 0);
		if (Renderer)
			SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		std::cout << "Renderer initialised!" << std::endl;

		isRunning = true;
	}

	map = new Map("Assets/room_builder_tileset.png", 1, 32);
	map->LoadMap("Assets/map.txt", 50, 20);

	Player.addComponent<TransformComponent>(2);
	Player.addComponent<SpriteComponent>("Assets/player_anims.png", true);
	Player.addComponent<ColliderComponent>("Player");
	Player.addComponent<KeyboardController>();
	Player.addGroup(groupPlayers);

	Object.addComponent<TransformComponent>(1400.0f, 200.0f);
	Object.addComponent<SpriteComponent>("Assets/suitcase.png");
	Object.addComponent<ColliderComponent>("Suitcase");
	Object.addComponent<ItemComponent>(1, 2);
	Object.addGroup(groupObjects);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& objects(manager.getGroup(Game::groupObjects));
auto& objectives(manager.getGroup(Game::groupObjectives));

void Game::handleEvents() {

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() {

	SDL_Rect playerCollider = Player.getComponent<ColliderComponent>().collider;
	Vector2D playerPosition = Player.getComponent<TransformComponent>().position;

	SDL_Rect objectCollider = Object.getComponent<ColliderComponent>().collider;
	Vector2D objectPosition = Object.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {

		SDL_Rect cCollider = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCollider, playerCollider)) {

			Player.getComponent<TransformComponent>().position = playerPosition;
		}
	}

	for (auto& obj : objectives) {

		SDL_Rect objectiveCollider = obj->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(objectiveCollider, objectCollider) && !Player.getComponent<KeyboardController>().isCarrying) {
			
			counter++;
			std::cout << "Score: " << counter << std::endl;
			
			Object.getComponent<TransformComponent>().position.x = 1400.0f;
			Object.getComponent<TransformComponent>().position.y = 200.0f;
		}

	}

	for (auto& o : objects) {

		if (Collision::AABB(objectCollider, playerCollider) && Player.getComponent<KeyboardController>().isCarrying) {
			//std::cout << "hit" << std::endl;
			Object.getComponent<TransformComponent>().position.x = playerPosition.x + 32;
			Object.getComponent<TransformComponent>().position.y = playerPosition.y + 32;
		}
	}
	
	camera.x = static_cast<int>(Player.getComponent<TransformComponent>().position.x - 320.0f);
	camera.y = static_cast<int>(Player.getComponent<TransformComponent>().position.y - 200.0f);

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;

}

void Game::render() {

	SDL_RenderClear(Renderer);

	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& c : colliders) {
		c->draw();
	}

	for (auto& obj : objectives) {
		obj->draw();
	}

	for (auto& o : objects) {
		o->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	SDL_RenderPresent(Renderer);
}

void Game::clean() {

	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}
