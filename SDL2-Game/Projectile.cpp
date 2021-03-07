#include "Projectile.h"

Projectile::Projectile(SDL_Rect position, float angle, std::string expression, Game* instance) : Gameobject(instance)
{
	instance->registerGameobject(this);
	sprite = new Sprite("../assets/PlasmaProjectile_a.png",2, 11, 11, 200, instance);
	sprite->setSize(position.w, position.h);
	instance->registerGameobject(sprite);
	start_position = position;
	this->position = start_position;
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
	sprite->setPosition(position.x, position.y);
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

	position.x = xnew + start_position.x - sprite->dimension->w/2;
	position.y = ynew + start_position.y - sprite->dimension->h/2;
}

void Projectile::checkCollision()
{
	auto collideobjects = collision();

	for (int i = 0; i < collideobjects.size(); i++)
	{
		if (collideobjects[i]->type == "Enemy")
		{
			Enemy* e = (Enemy*)collideobjects[i];
			e->sprite->setVisible(false);
			e->screech();
		}
		if (collideobjects[i]->type == "Wall")
		{
			delete this;
			return;
		}
	}
}
