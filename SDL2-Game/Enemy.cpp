#include "Enemy.h"

Enemy::Enemy(SDL_Rect position,Game* instance): Gameobject(instance)
{
	sprite = new Sprite("../assets/Alien_a.png", 2, 16, 16, 300, instance);
	instance->registerGameobject(sprite);
	sprite->setSize(position.w, position.h);
	sprite->setPosition(position.x, position.y);
	this->position = position;
	m_screech = Mix_LoadWAV("../assets/Monster_screech.mp3");
	type = "Enemy"; 
}

Enemy::~Enemy()
{
	delete sprite;
}

void Enemy::update(int delta)
{
}

void Enemy::render()
{
}

void Enemy::screech()
{
	if (!dead)
	{
		Mix_Volume(2, MIX_MAX_VOLUME);
		Mix_PlayChannel(2, m_screech, 0);
		dead = true;
	}

}
