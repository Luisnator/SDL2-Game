#pragma once
#include "Gameobject.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureLoader.h"
#include <string.h>
class Background : public Gameobject
{
public:
	Background(std::string path,Game* instance);
	~Background();
	SDL_Texture* image;
	void update(int delta);
	void render();
};

