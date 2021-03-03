#pragma once
#include "SDL.h"
#include "Game.h"
#include <string>
#include <typeinfo>
class Gameobject
{
public:
	Gameobject(Game* instance);
	~Gameobject();

	Game* instance;
	std::string type;
	virtual void update(int delta);
	virtual void render();
};