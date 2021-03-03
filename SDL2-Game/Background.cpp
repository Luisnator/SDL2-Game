#include "Background.h"

Background::Background(std::string path, Game* instance) : Gameobject(instance)
{
	image = TextureLoader::loadTexture(path, instance->renderer);
	type = "Background";
}

Background::~Background()
{
}

void Background::update(int delta)
{
}

void Background::render()
{
	SDL_RenderCopy(instance->renderer, image, NULL, NULL);
}
