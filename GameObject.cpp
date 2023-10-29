#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {

	objectTexture = TextureManager::loadTexture(textureSheet);

	xpos = x;
	ypos = y;
}

GameObject::~GameObject() {

}

void GameObject::Update() {

	xpos++;
	ypos++;

	srcRectangle.h = 32;
	srcRectangle.w = 32;
	srcRectangle.x = 0;
	srcRectangle.y = 0;

	destRectangle.x = xpos;
	destRectangle.y = ypos;
	destRectangle.w = srcRectangle.w * 2;
	destRectangle.h = srcRectangle.h * 2;

}

void GameObject::Render() {

	SDL_RenderCopy(Game::Renderer, objectTexture, NULL, &destRectangle);
}