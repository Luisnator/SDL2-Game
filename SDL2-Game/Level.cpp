#include "Level.h"

Level::Level(Game* instance):Gameobject(instance)
{
	type = "Level";
}

Level::~Level()
{
	std::cout << "Level delete" << std::endl;
	for (int i = 0; i < lvlObjects.size(); i++)
	{
		instance->unregisterGameobject(lvlObjects[i]);
		delete lvlObjects[i];
	}
}

void Level::update(int delta)
{
}

void Level::render()
{
}

void Level::createGameobject(Gameobject* go)
{
	lvlObjects.push_back(go);
	instance->registerGameobject(go);
}

