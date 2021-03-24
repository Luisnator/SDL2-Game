#include "Gameobject.h"
Gameobject::Gameobject(Game* instance)
{
	this->instance = instance;
}

Gameobject::~Gameobject()
{
}

void Gameobject::update(int delta)
{
}

void Gameobject::render()
{
}

std::vector<Gameobject*> Gameobject::collision()
{
	std::vector<Gameobject*> collidedObjects;
	auto gameobjects = instance->getGameobjects();
	for (int i = 0; i < gameobjects.size(); i++)
	{
		Gameobject* go = gameobjects[i];
		bool collide = true;

		if ((go->position.y + go->position.h <= position.y) || 
			(go->position.y >= position.y + position.h) || 
			(go->position.x + go->position.w <= position.x) || 
			(go->position.x >= position.x + position.w))
		{
			collide = false;
		}
		if (collide == true)
		{
			collidedObjects.push_back(go);
		}
	}
	return collidedObjects;
}
