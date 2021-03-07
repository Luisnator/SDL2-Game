#include "Background.h"

Background::Background(std::string path, Game* instance) : Gameobject(instance)
{
	image = TextureLoader::loadTextureFromImage(path, instance->renderer);
	type = "Background";
}

Background::~Background()
{
	SDL_DestroyTexture(image);
}

void Background::update(int delta)
{
}

void Background::render()
{
	SDL_RenderCopy(instance->renderer, image, NULL, NULL);
}
