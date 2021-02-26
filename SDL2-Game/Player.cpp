#include "Player.h"
#include "TextureLoader.h"
#include "exprtk.hpp"
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
	
	for (double i = 0; i < 5000; i += 5)
	{
		x = i;
		double y = expression.value();
		y = -y;
		SDL_Rect fillRect = { position[0]+ x + width , position[1] + y+(hight/2), 5, 5 };
		SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(instance->renderer, &fillRect);
	}
	//Get mouse position
	int x_m, y_m;
	SDL_GetMouseState(&x_m, &y_m);
	SDL_Rect mouse = { x_m,y_m,5,5 };
	SDL_RenderFillRect(instance->renderer, &mouse);

}
