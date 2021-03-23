#include "Game.h"
#include "Gameobject.h"
#include "Player.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
Game::Game()
{
}

Game::~Game()
{
	for (int i = 0; i < gameobjects.size(); i++)
	{
		if (gameobjects[i]->type == "Level")
		{
			delete gameobjects[i];
		}
	}
}

void Game::init(std::string title, int xpos, int ypos, int width, int height, int flags)
{
	window_w = width;
	window_h = height;
	if (!SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL_Subsystem crash" << std::endl;
		exit(0);
	}
	window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
	if (!window)
	{
		std::cout << "Window crash" << std::endl;
		exit(0);
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cout << "Renderer crash" << std::endl;
		exit(0);
	}
	if (!Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0)
	{
		std::cout << "Mix crash" << std::endl;
		exit(0);
	}
	if (!TTF_Init() == 0)
	{
		std::cout << "TTF crash" << std::endl;
		exit(0);
	}
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		loop = false;
		break;
	default:
		break;
	}
}

void Game::update(int delta)
{
	for (int i = 0; i < gameobjects.size(); i++)
	{
		gameobjects[i]->update(delta);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& value : gameobjects)
	{
		value->render();
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::registerGameobject(Gameobject* go)
{
	gameobjects.push_back(go);
}

void Game::unregisterGameobject(Gameobject* go)
{
	for (int i = 0; i < gameobjects.size(); i++)
	{
		if (gameobjects[i] == go)
		{
			gameobjects.erase(gameobjects.begin() + i);
		}
	}
}

std::vector<Gameobject*> Game::getGameobjects()
{
	return gameobjects;
}
