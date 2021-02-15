#include "Player.h"

Player::Player(Game* instance) : Gameobject(instance)
{
	playerTex = nullptr;
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	SDL_Surface* tmpSurface = IMG_Load("../assets/sprite_0.png");
	if (tmpSurface == NULL)
	{
		printf("Unable to load image %s\n", IMG_GetError());
	}
	playerTex = SDL_CreateTextureFromSurface(instance->renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

Player::~Player()
{
}

void Player::update(int delta)
{

}

void Player::render()
{
	SDL_RenderCopy(instance->renderer, playerTex, NULL, NULL);
	//cout << "render_player" << endl;
}