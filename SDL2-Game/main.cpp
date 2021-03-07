#include "SDL.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Wall.h"
#include "Level_One.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	int tickstart = SDL_GetTicks();
	int tickend = SDL_GetTicks();
	Level_One* lvl1 = new Level_One(game);
	game->registerGameobject(lvl1);
	while (game->isRunning)
	{
		int delta = tickend - tickstart;
		game->handleEvents();
		tickstart = SDL_GetTicks();
		game->update(delta);
		game->render();
		tickend = SDL_GetTicks();
	}
	game->clean();
	
	return 0;
}