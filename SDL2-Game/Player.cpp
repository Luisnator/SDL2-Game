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
	sprite->setPosition(100, 100);
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