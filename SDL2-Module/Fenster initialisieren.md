---
layout: default
title: Fenster initialisieren
parent: SDL2-Module
nav_order: 1
---

# Fenster in SDL2 initialisieren

Der einfachste Weg ein Fenster in SDL2 zu erstellen geht mithilfe der folgenden beiden Befehlszeilen:

```cpp
#include "SDL2.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Tolles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	while(true)
	{}
}
```

Dies ist allerdings kein eleganter und modularer Ansatz, deswegen empfiehlt es sich eine Klasse für das Spiel zu erstellen.

```cpp
//Game.h
class Game
{
public:
	Game();
	~Game();
	void init(std::string title, int xpos, int ypos, int width, int height, int flags);
	void clean();

	SDL_Window* window;
	bool isRunning;

	int window_w = 0;
	int window_h = 0;
	
};
```
Mit der init Funktion wird das Fenster initialisiert. Die Parameter xpos und ypos sind Koordinaten für die Position des Fensters. 
Mit width und height wird die Auflösung des Fensters bestimmt. Und mit dem Parameter flags kann man bestimmen auf welche Art das Fenster erstellt wird.
Für alle verfügbaren Flags bitte [hier](https://wiki.libsdl.org/SDL_CreateWindow) nachschauen.

Mit der Funktion clean werden beim Beenden des Programms, die SDL2 Funktionalitäten korrekt geschlossen.

In dem Pointer window wird das erstellte Fenster gespeichert.

Mit dem bool isRunning wird festgehalten, ob das Spiel läuft oder beendet werden soll.

Die Integer window_w und window_h speichern die Breite und Höhe des Fensters.

```cpp
//Game.cpp
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
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}
```
So könnte man die Funktion init ausformulieren.

```cpp
//Game.cpp
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "bye" << std::endl;
}
```
In der Funktion clean sollten alle offenen Objekte zerstört und alle Systemressourcen freigegeben werden. 

```cpp
//main.cpp
int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	while (game->isRunning)
	{
	}
	game->clean();
	
	return 0;
}
```
In der main Funktion wird das Game-Objekt erstellt und anschließend wird die Spielschleife gestartet.

# Dokumentation zu den hier verwendeten SDL2 Funktionen

[SDL_Init](https://wiki.libsdl.org/SDL_Init)
[SDL_CreateWindow](https://wiki.libsdl.org/SDL_CreateWindow)
[SDL_DestroyWindow](https://wiki.libsdl.org/SDL_DestroyWindow)
[SDL_Quit](https://wiki.libsdl.org/SDL_Quit)


