#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureLoader.h"
#include <vector>
using namespace std;

class Sprite
{
public:
	Sprite(string file, int frames, int width, int height,int speed, SDL_Renderer* renderer);
	~Sprite();
	vector<SDL_Rect*> spriteClips;
	SDL_Texture* sourceTexture;
	int active_clip = 0;
	int speed;
	int frames;
	void update(int delta);
	void render();
};

