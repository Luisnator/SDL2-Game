#include "Player.h"
#include "TextureLoader.h"
#include "exprtk.hpp"
#include <tgmath.h>
#include "Projectile.h"
Player::Player(Game* instance) : Gameobject(instance)
{
	sprite = new Sprite("../assets/Robot_with_jetpack.png", 4, 16, 16, 200, instance);
	instance->registerGameobject(sprite);
	sprite->setSize(position.w, position.h);

	plasmaShot = Mix_LoadWAV("../assets/PlasmaShot.mp3");

	text = TextureLoader::loadTextureFromText("0", { 0,0,0 }, instance->renderer);
	type = "Player";
}

Player::~Player()
{
}

void Player::update(int delta)
{
	this->delta = delta;

	checkInput(delta);

	sprite->setPosition(position.x, position.y);

	std::string appendix; 
	SDL_Color c;
	if (!toggle_input)
	{
		c = { 0,0,0};
		appendix = "     | press F to edit";
	}
	else
	{
		c = { 255,0,0 };
		appendix = "<-- Confirm with Enter";
	}

	SDL_DestroyTexture(text);
	std::string renderText;
	renderText = "Smart Gun Equation:  " + expression_string + appendix;
	text = TextureLoader::loadTextureFromText(renderText, c, instance->renderer);
}

void Player::checkInput(int delta)
{
	static int t = 501;
	const int threshold = 1000;
	t += delta;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (!toggle_input)
	{
		SDL_StopTextInput();
		if (state[SDL_SCANCODE_UP]) {
			position.y -= speed * delta;
		}
		if (state[SDL_SCANCODE_DOWN]) {
			position.y += speed * delta;
		}
		if (state[SDL_SCANCODE_RIGHT]) {
			position.x += speed * delta;
			sprite->setHorizontalFlip(false);
		}
		if (state[SDL_SCANCODE_LEFT]) {
			position.x -= speed * delta;
			sprite->setHorizontalFlip(true);
		}
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK && t > threshold)
		{
			Mix_Volume(1, MIX_MAX_VOLUME / 2);
			Mix_PlayChannel(1, plasmaShot, 0);
			SDL_Rect corrected_pos = { position.x + position.w ,position.y + position.h / 2,25,25 };
			Projectile* p = new Projectile(corrected_pos, cur_angle, expression_string, instance);
			t = 0;
		}
		if (state[SDL_SCANCODE_F])
		{
			toggle_input = !toggle_input;
			SDL_Delay(200);
		}
	}
	else
	{
		SDL_StartTextInput();
		if (state[SDL_SCANCODE_RETURN])
		{
			toggle_input = !toggle_input;
			SDL_Delay(200);
		}
		if (instance->event.type == SDL_KEYDOWN)
		{
			if (instance->event.key.keysym.sym == SDLK_BACKSPACE && expression_string.length() > 0)
			{
				expression_string.pop_back();
				SDL_Delay(200);
			}
		}
		else if (state[SDLK_CARET])
		{
			expression_string += "^";
			SDL_Delay(200);
		}
		else if (instance->event.type == SDL_TEXTINPUT)
		{
			std::string key = instance->event.text.text;
			if (key == "#")
			{
				expression_string += "^";
			}
			else
			{
				expression_string += key;
			}
			//expression_string += instance->event.text.text;
			SDL_Delay(200);
		}
		
	}




}

void Player::render()
{
	static SDL_Rect* rec = new SDL_Rect;
	rec->x = 50;
	rec->y = 50;
	rec->w = TextureLoader::width;
	rec->h = TextureLoader::height;
	calculateFunction();
	SDL_RenderCopy(instance->renderer, text, NULL, rec);
}

void Player::calculateFunction()
{
	if (toggle_input)
	{
		return;
	}
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;
	//expression_string = "sin(x)";//"x^2-2x";//"sin(2*x)-2*sin(x)";//////"1/1000*x^2";//

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

	float normalized_pos[2] = { (position.x) / sqrt(pow(position.x,2) + pow(position.y,2)),position.y / sqrt(pow(position.x, 2) + pow(position.y, 2)) };
	float mouse_vector[2] = { x_m - (position.x + position.w),y_m - (position.y + position.h / 2) };
	float mousemagitude = sqrt(pow(double(mouse_vector[0]), 2.0) + pow(mouse_vector[1], 2));
	float forward_vector[2] = { 1,0 };
	float normalized_mouse[2] = { (mouse_vector[0] / mousemagitude) , (mouse_vector[1] / mousemagitude) };

	float angle = acos((normalized_mouse[0] * forward_vector[0] + normalized_mouse[1] * forward_vector[1]) / (sqrt(pow(normalized_mouse[0], 2) + pow(normalized_mouse[1], 2)) * (sqrt(pow(forward_vector[0], 2) + pow(forward_vector[1], 2)))));

	for (double i = 0; i < 500; i += 0.1)
	{
		float mod_angle = angle;
		if (y_m < position.y + position.h / 2)
		{
			mod_angle = -mod_angle;
		}
		x = i;
		double y = expression.value();
		y = -y * 100;
		float s = sin(mod_angle);
		float c = cos(mod_angle);

		float xnew = x * 100 * c - y * s;
		float ynew = x * 100 * s + y * c;

		x = xnew + position.x;
		y = ynew + position.y;
		cur_angle = mod_angle;
		SDL_Rect fillRect = { x + position.w ,y + (position.h / 2), 5, 5 };
		SDL_RenderFillRect(instance->renderer, &fillRect);
	}


}
