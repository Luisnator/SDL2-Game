#include "Wall.h"

Wall::Wall(SDL_Rect position, Game* instance):Gameobject(instance)
{
	this->position = position;
	sprite = new Sprite("../assets/concrete.png", 1, 16, 16, 200, instance);
	sprite->setSize(position.w,position.h);
	sprite->setPosition(position.x, position.y);
	instance->registerGameobject(sprite);
	type = "Wall";
}

Wall::~Wall()
{
	instance->unregisterGameobject(sprite);
	delete sprite;	
}

void Wall::update(int delta)
{
}

void Wall::render()
{

}
