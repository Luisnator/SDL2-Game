#pragma once
#include "Gameobject.h"
#include "Game.h"
#include "Sprite.h"
#include <string.h>
#include "exprtk.hpp"
#include "Enemy.h"

class Projectile 
	: public Gameobject
{
public:
	Projectile(SDL_Rect position, float angle,std::string expression, Game* instance);
	~Projectile();

	Sprite* sprite;
	std::string expression_string;
	double x = 0;
	float angle = 0;
	SDL_Rect start_position = { 0,0,0,0 };
	SDL_Rect current_position = { 0,0,0,0 };
	int t = 0;

	void update(int delta);
	void render();
	void calculateFunction(int delta);
	void checkCollision();

};

