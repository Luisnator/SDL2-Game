#include "SDL.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	Background* bg = new Background("../assets/urban-landscape-background.png",game);
	game->registerGameobject(bg);
	Player* player = new Player(game);
	game->registerGameobject(player);
	Enemy* enemy = new Enemy({500,500,100,100}, game);
	game->registerGameobject(enemy);
	Enemy* enemy2 = new Enemy({ 750,300,100,100 }, game);
	game->registerGameobject(enemy2);
	int tickstart = SDL_GetTicks();
	int tickend = SDL_GetTicks();
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