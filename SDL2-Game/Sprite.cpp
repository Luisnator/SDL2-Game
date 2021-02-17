#include "Sprite.h"

Sprite::Sprite(string file, int frames, int width, int height,int speed, SDL_Renderer* renderer)
{
	sourceTexture = TextureLoader::loadTexture(file,renderer);
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