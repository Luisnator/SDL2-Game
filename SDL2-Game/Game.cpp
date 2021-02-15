#include "Game.h"
#include "Gameobject.h"
#include "Player.h"
Game::Game()
{
	isRunning = false;
	renderer = nullptr;
	window = nullptr;
}

Game::~Game()
{
}

void Game::init(string title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems Initialised" << endl;
		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
		if (window)
		{
			cout << "Window created" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created" << endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	for (auto & value : gameobjects)
	{
		value->update(10);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& value : gameobjects)
	{
		value->render();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "bye" << endl;
}

void Game::registerGameobject(Gameobject* go)
{
	gameobjects.push_back(go);
}
