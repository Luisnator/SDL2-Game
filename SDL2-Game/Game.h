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
	void registerGameobject(Gameobject* go);

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Gameobject*> gameobjects;
	bool isRunning;
	
};

