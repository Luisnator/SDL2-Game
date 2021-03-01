#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureLoader.h"
#include <vector>
#include "Gameobject.h"

class Sprite :
	public Gameobject
{
public:
	Sprite(std::string file, int frames, int width, int height, int speed, Game* instance);
	~Sprite();
	std::vector<SDL_Rect*> spriteClips;
	SDL_Texture* sourceTexture;
	int active_clip = 0;
	int speed;
	int frames;
	bool visible = true;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect* dimension;
	void update(int delta);
	void render();
	SDL_Rect* getActiveClip();
	void setSize(int width, int height);
	void setPosition(int x, int y);
	void setVisible(bool visible);
	void setHorizontalFlip(bool flip);
};

