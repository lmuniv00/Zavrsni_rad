#pragma once
#include "EntityComponents.h"
#include "SDL.h"

class TileComponent : public Component {

public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tile_size, int tile_scale, const char* path) {

		texture = TextureManager::loadTexture(path);

		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tile_size;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tile_size * tile_scale;
	}

	void update() override {

		destRect.x = static_cast<int>(position.x) - Game::camera.x;
		destRect.y = static_cast<int>(position.y) - Game::camera.y;

	}

	void draw() override {

		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);

	}
};
