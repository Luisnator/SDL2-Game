#include "Game.h"
#include "Gameobject.h"
#include "Player.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
Game::Game()
{
	isRunning = false;
	renderer = nullptr;
	window = nullptr;
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
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised" << std::endl;
		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
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
	std::cout << "bye" << std::endl;
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
