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
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = go->position.x;
		rightA = go->position.x + go->position.w;
		topA = go->position.y;
		bottomA = go->position.y + go->position.h;

		//Calculate the sides of rect B
		leftB = position.x;
		rightB = position.x + position.w;
		topB = position.y;
		bottomB = position.y + position.h;

		bool collide = true;
		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			collide = false;
		}

		if (topA >= bottomB)
		{
			collide = false;
		}

		if (rightA <= leftB)
		{
			collide = false;
		}

		if (leftA >= rightB)
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
