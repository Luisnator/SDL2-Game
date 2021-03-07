#include "Sprite.h"

Sprite::Sprite(std::string file, int frames, SDL_Rect position,int speed, Game* instance) : Gameobject(instance)
{
	sourceTexture = TextureLoader::loadTextureFromImage(file,instance->renderer);
	this->frames = frames;
	this->speed = speed;
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect* spriteFrame = new SDL_Rect;
		spriteFrame->x = i * position.w;
		spriteFrame->y = 0;
		spriteFrame->w = position.w;
		spriteFrame->h = position.h;
		spriteClips.push_back(spriteFrame);
	}
	this->position = position;
	type = "Sprite";
}
Sprite::~Sprite()
{
	instance->unregisterGameobject(this);
	for (int i = 0; i < spriteClips.size(); i++)
	{
		delete spriteClips[i];
	}
	SDL_DestroyTexture(sourceTexture);
}
SDL_Rect* Sprite::getActiveClip()
{
	return spriteClips[active_clip];
}
void Sprite::update(int delta)
{
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
	position.w = width;
	position.h = height;
}

void Sprite::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Sprite::render()
{
	if (visible)
	{
		SDL_RenderCopyEx(instance->renderer,sourceTexture,getActiveClip(), &position, NULL, NULL, flip);
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