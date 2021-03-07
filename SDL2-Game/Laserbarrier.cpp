#include "Laserbarrier.h"

Laserbarrier::Laserbarrier(SDL_Rect position, Game* instance):Gameobject(instance)
{
	this->position = position;
	sprite = new Sprite("../assets/Laserbarrier.png", 1, 16, 16, 200, instance);
	sprite->setSize(position.w, position.h);
	sprite->setPosition(position.x, position.y);
	instance->registerGameobject(sprite);
	type = "Laserbarrier";
}

Laserbarrier::~Laserbarrier()
{
	delete sprite;
}

void Laserbarrier::update(int delta)
{
}

void Laserbarrier::render()
{
}
