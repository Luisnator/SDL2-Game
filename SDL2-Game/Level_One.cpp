#include "Level_One.h"

Level_One::Level_One(Game* instance):Level(instance)
{
	createGameobject(new Background("../assets/urban-landscape-background.png", instance));
	createGameobject(new Laserbarrier({ 500,100,20,2000}, instance));
	createGameobject(new Laserbarrier({ 0,100,500,20 }, instance));
	createGameobject(new Laserbarrier({ 0,instance->window_h+20,500,20 },instance));
	createGameobject(new Laserbarrier({ -20,100,20,2000 }, instance));
	createGameobject(new Player(instance));
	createGameobject(new Enemy({ 700,500,100,100 }, instance));
	createGameobject(new Wall({ 700,600,100,1000 }, instance));
	createGameobject(new Enemy({ 1000,350,100,100 }, instance));
	createGameobject(new Wall({ 1000,450,100,1000 }, instance));
	createGameobject(new Enemy({ 1300,500,100,100 }, instance));
	createGameobject(new Wall({ 1300,600,100,1000 }, instance));
	createGameobject(new Enemy({ 1600,350,100,100 }, instance));
	createGameobject(new Wall({ 1600,450,100,1000 }, instance));
}

Level_One::~Level_One()
{

}

void Level_One::update(int delta)
{

	SDL_PollEvent(&instance->event);
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_R]) {
		Level_One* lo = new Level_One(instance);
		instance->unregisterGameobject(this);
		instance->registerGameobject(lo);
		SDL_Delay(200);
		delete this;
	}

}

void Level_One::render()
{
}

