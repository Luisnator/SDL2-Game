#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
class Gameobject;
class Player;
#include <vector>

class Game
{
public:
	Game();
	~Game();
	void init(std::string title, int xpos, int ypos, int width, int height, int flags);
	void handleEvents();
	void update(int delta);
	void render();
	void clean();
	void GameLoop();
	void registerGameobject(Gameobject* go);
	void unregisterGameobject(Gameobject* go);
	std::vector<Gameobject*> getGameobjects();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<Gameobject*> gameobjects;
	SDL_Event event;
	bool loop = true;

	int window_w = 0;
	int window_h = 0;
	
};

