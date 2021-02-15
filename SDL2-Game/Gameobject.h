#pragma once
#include "SDL.h"
#include "Game.h"
class Gameobject
{
public:
	Gameobject(Game* instance);
	~Gameobject();

	Game* instance;
	virtual void update(int delta);
	virtual void render();
};