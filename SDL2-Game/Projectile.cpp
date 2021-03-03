#include "Projectile.h"

Projectile::Projectile(SDL_Rect position, float angle, std::string expression, Game* instance) : Gameobject(instance)
{
	instance->registerGameobject(this);
	sprite = new Sprite("../assets/PlasmaProjectile.png",1, 16, 16, 200, instance);
	sprite->setSize(50, 50);
	instance->registerGameobject(sprite);
	start_position = position;
	current_position = start_position;
	this->angle = angle;
	expression_string = expression;
	type = "Projectile";
}

Projectile::~Projectile()
{
	delete sprite;
	instance->unregisterGameobject(this);
}

void Projectile::update(int delta)
{
	const int lifetime = 4000;
	calculateFunction(delta);
	sprite->setPosition(current_position.x, current_position.y);
	checkCollision();
	if (t > lifetime)
	{
		t = 0;
		delete this;
	}
	t += delta;
}

void Projectile::render()
{
}

void Projectile::calculateFunction(int delta)
{
	x += delta * 0.005;
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;

	symbol_table_t symbol_table;
	symbol_table.add_variable("x", x);
	symbol_table.add_constants();


	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);

	double y = expression.value();
	y = -y * 100;
	float s = sin(angle);
	float c = cos(angle);

	float xnew = x * 100 * c - y * s;
	float ynew = x * 100 * s + y * c;

	current_position.x = xnew + start_position.x - sprite->dimension->w/2;
	current_position.y = ynew + start_position.y - sprite->dimension->h/2;
}

void Projectile::checkCollision()
{
	auto gameobjects = instance->getGameobjects();
	for (int i = 0; i < gameobjects.size()-1; i++)
	{
		std::string filter = "Enemy";
		std::string source = gameobjects[i]->type;
		if(source == filter)
		{
			Enemy* e = (Enemy*)gameobjects[i];
			//The sides of the rectangles
			int leftA, leftB;
			int rightA, rightB;
			int topA, topB;
			int bottomA, bottomB;

			//Calculate the sides of rect A
			leftA = e->position.x;
			rightA = e->position.x + e->position.w;
			topA = e->position.y;
			bottomA = e->position.y + e->position.h;

			//Calculate the sides of rect B
			leftB = current_position.x;
			rightB = current_position.x + current_position.w;
			topB = current_position.y;
			bottomB = current_position.y + current_position.h;

			bool collide = true;
			//If any of the sides from A are outside of B
			if (bottomA <= topB)
			{
				collide =  false;
			}

			if (topA >= bottomB)
			{
				collide =  false;
			}

			if (rightA <= leftB)
			{
				collide =  false;
			}

			if (leftA >= rightB)
			{
				collide = false;
			}
			
			if (collide == true)
			{
				e->sprite->setVisible(false);
				e->screech();
			}
		}

		
	}
}
