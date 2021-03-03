#pragma once
#include "Gameobject.h"
#include "Game.h"
#include "Sprite.h"
#include <string.h>
#include "exprtk.hpp"

class Projectile 
	: public Gameobject
{
public:
	Projectile(int position[], float angle,std::string expression, Game* instance);
	~Projectile();

	Sprite* sprite;
	std::string expression_string;
	double x = 0;
	float angle = 0;
	float start_position[2] = { 0,0 };
	float current_position[2] = { 0,0 };
	int t = 0;

	void update(int delta);
	void render();
	void calculateFunction(int delta);

};

