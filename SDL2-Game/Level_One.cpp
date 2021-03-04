#include "Level_One.h"

Level_One::Level_One(Game* instance):Level(instance)
{
	createGameobject(new Background("../assets/urban-landscape-background.png", instance));
	createGameobject(new Player(instance));
	createGameobject(new Enemy({ 700,500,100,100 }, instance));
	createGameobject(new Wall({ 700,600,100,1000 }, instance));
	createGameobject(new Enemy({ 1000,300,100,100 }, instance));
	createGameobject(new Wall({ 1000,400,100,1000 }, instance));
	createGameobject(new Enemy({ 1300,500,100,100 }, instance));
	createGameobject(new Wall({ 1300,600,100,1000 }, instance));
	createGameobject(new Enemy({ 1600,300,100,100 }, instance));
	createGameobject(new Wall({ 1600,400,100,1000 }, instance));
}

Level_One::~Level_One()
{
}
