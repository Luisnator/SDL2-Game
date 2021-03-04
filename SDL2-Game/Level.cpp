#include "Level.h"

Level::Level(Game* instance):Gameobject(instance)
{
	type = "Level";
}

Level::~Level()
{
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

