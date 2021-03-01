#include "Player.h"
#include "TextureLoader.h"
#include "exprtk.hpp"
#include <tgmath.h>
Player::Player(Game* instance) : Gameobject(instance)
{
	playerTex = nullptr;
	playerTex = TextureLoader::loadTexture("../assets/sprite_0.png",instance->renderer);
	sprite = new Sprite("../assets/Bug_idle1.png", 5, 16, 16, 200, instance);
	instance->registerGameobject(sprite);
	sprite->setSize(width, hight);
	punchSound = Mix_LoadWAV("../assets/Punch Sound Effect.mp3");
}

Player::~Player()
{
}

void Player::update(int delta)
{
	this->delta = delta;
	checkInput();
	sprite->setPosition(position[0], position[1]);
}

void Player::checkInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_UP]) {
		position[1] -= speed*delta;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		position[1] += speed*delta;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		position[0] += speed * delta;
		sprite->setHorizontalFlip(false);
	}
	if (state[SDL_SCANCODE_LEFT]) {
		position[0] -= speed * delta;
		sprite->setHorizontalFlip(true);
	}
	if (state[SDL_SCANCODE_F])
	{
		Mix_Volume(1, MIX_MAX_VOLUME / 2);
		Mix_PlayChannel(1, punchSound, 0);

	}
	
}

void Player::render()
{
	static SDL_Rect* rec = new SDL_Rect;
	rec->x = 0;
	rec->y = 0;
	rec->w = 100;
	rec->h = 100;
	//SDL_RenderCopy(instance->renderer, playerTex, NULL, NULL);
	//cout << "render_player" << endl;
	calculateFunction();
}

void Player::calculateFunction()
{
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;
	std::string expression_string = "100*sin(x*0.01)";
	
	double x = 1;

	symbol_table_t symbol_table;
	symbol_table.add_variable("x", x);
	symbol_table.add_constants();


	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);
	

	SDL_SetRenderDrawColor(instance->renderer, 0x00, 0xFF, 0x00, 0xFF);

	//Get mouse position
	int x_m, y_m;
	SDL_GetMouseState(&x_m, &y_m);
	SDL_Rect mouse = { x_m,y_m,5,5 };

	SDL_RenderFillRect(instance->renderer, &mouse);

	float normalized_pos[2] = {(position[0])/sqrt(pow(position[0],2)+pow(position[1],2)),position[1] / sqrt(pow(position[0], 2) + pow(position[1], 2)) };
	float mouse_vector[2] = { x_m - (position[0]+width),y_m - (position[1]+hight/2) };
	float mousemagitude = sqrt(pow(double(mouse_vector[0]),2.0) + pow(mouse_vector[1],2));
	float forward_vector[2] = { 1,0 };
	float normalized_mouse[2] = { (mouse_vector[0] /mousemagitude) , (mouse_vector[1] / mousemagitude) };

	float test =  acos((normalized_mouse[0] * normalized_pos[0] + normalized_mouse[1] * normalized_pos[1]));
	float angle = acos((normalized_mouse[0]* forward_vector[0] + normalized_mouse[1] * forward_vector[1]) / (sqrt(pow(normalized_mouse[0],2) + pow(normalized_mouse[1],2)) * (sqrt(pow(forward_vector[0],2) + pow(forward_vector[1],2)))));
	std::cout << x_m  <<" " << mousemagitude << "" << normalized_mouse[0] <<" " << normalized_mouse[1]<< " " << x_m << std::endl;
	 
	for (double i = 0; i < 5000; i += 5)
	{
		float mod_angle = angle;
		if (y_m < position[1] + hight / 2)
		{
			mod_angle = -mod_angle;
		}
		x = i;
		double y = expression.value();
		y = -y;
		float s = sin(mod_angle);
		float c = cos(mod_angle);

		//x -= position[0];
		//y -= position[1];

		float xnew = x * c - y * s;
		float ynew = x * s + y * c;

		x = xnew + position[0];
		y = ynew + position[1];

		SDL_Rect fillRect = { x + width ,y+(hight/2), 5, 5 };
		SDL_RenderFillRect(instance->renderer, &fillRect);
		//cout << x << "  " << y << endl;
	}


}
