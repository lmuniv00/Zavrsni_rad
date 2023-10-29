#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* texture) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(Game::Renderer, tex, &src, &dest, NULL, NULL, flip);
}