#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
class TextureLoader
{
public:
	static SDL_Texture* loadTextureFromImage(std::string path,SDL_Renderer* renderer,int flags = IMG_INIT_PNG);
	static SDL_Texture* loadTextureFromText(std::string text,SDL_Color color,int size,SDL_Renderer* renderer);
	static int height;
	static int width;
};

