#include "Projectile.h"

Projectile::Projectile(int position[], float angle, std::string expression, Game* instance) : Gameobject(instance)
{
	instance->registerGameobject(this);
	sprite = new Sprite("../assets/PlasmaProjectile.png",1, 16, 16, 200, instance);
	sprite->setSize(50, 50);
	instance->registerGameobject(sprite);
	start_position[0] = position[0];
	start_position[1] = position[1];
	this->angle = angle;
	expression_string = expression;
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
	sprite->setPosition(current_position[0], current_position[1]);
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

	current_position[0] = xnew + start_position[0];
	current_position[1] = ynew + start_position[1];
}
