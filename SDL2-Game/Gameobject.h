#pragma once
#include "SDL.h"
#include "Game.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <algorithm>
class Gameobject
{
public:
	Gameobject(Game* instance);
	~Gameobject();

	Game* instance;
	std::string type;

	SDL_Rect position = {0,0,0,0};

	virtual void update(int delta);
	virtual void render();

	std::vector<Gameobject*> collision();
};