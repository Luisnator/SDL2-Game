#include "Player.h"
#include "TextureLoader.h"
Player::Player(Game* instance) : Gameobject(instance)
{
	playerTex = nullptr;
	playerTex = TextureLoader::loadTexture("../assets/sprite_0.png",instance->renderer);
	sprite = new Sprite("../assets/Bug_idle1.png", 5, 16, 16, 200, instance);
	instance->registerGameobject(sprite);
	sprite->setSize(100, 100);
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
}