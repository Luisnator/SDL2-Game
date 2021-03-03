#include "Sprite.h"

Sprite::Sprite(std::string file, int frames, int width, int height,int speed, Game* instance) : Gameobject(instance)
{
	sourceTexture = TextureLoader::loadTexture(file,instance->renderer);
	this->frames = frames;
	this->speed = speed;
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect* spriteFrame = new SDL_Rect;
		spriteFrame->x = i * width;
		spriteFrame->y = 0;
		spriteFrame->w = width;
		spriteFrame->h = height;
		spriteClips.push_back(spriteFrame);
	}
	dimension = new SDL_Rect;
	dimension->x = 0;
	dimension->y = 0;
	dimension->w = width;
	dimension->h = height;
}
Sprite::~Sprite()
{
	instance->unregisterGameobject(this);
	delete dimension;
	for (int i = 0; i < spriteClips.size(); i++)
	{
		delete spriteClips[i];
	}
	SDL_free(sourceTexture);
}
SDL_Rect* Sprite::getActiveClip()
{
	return spriteClips[active_clip];
}
void Sprite::update(int delta)
{
	static int time = 0;
	time += delta;
	if (time > speed)
	{
		active_clip++;
		time = time - speed;
	}
	if (active_clip >= frames)
	{
		active_clip = 0;
	}
}
void Sprite::setSize(int width, int height)
{
	dimension->w = width;
	dimension->h = height;
}

void Sprite::setPosition(int x, int y)
{
	dimension->x = x;
	dimension->y = y;
}

void Sprite::render()
{
	if (visible)
	{
		SDL_RenderCopyEx(instance->renderer,sourceTexture,getActiveClip(), dimension, NULL, NULL, flip);
	}
}

void Sprite::setVisible(bool visible)
{
	this->visible = visible;
}

void Sprite::setHorizontalFlip(bool flip)
{
	if (flip)
	{
		this->flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		this->flip = SDL_FLIP_NONE;
	}
}