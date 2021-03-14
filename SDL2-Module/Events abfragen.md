---
layout: default
title: Events abfragen
parent: SDL2-Module
nav_order: 3
---

# Events abfragen

Events müssen in SDL2 aktiv abgefragt werden und funktionieren somit mit einem [Polling](https://de.wikipedia.org/wiki/Polling_(Informatik)) System.

```cpp
//Game.h
class Game
{
public:
	Game();
	~Game();
	void init(std::string title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void clean();
	void handleEvents(); // <-- neu

	SDL_Window* window;
	SDL_Renderer* renderer;
    SDL_Event event; // <-- neu
	bool isRunning;

	int window_w = 0;
	int window_h = 0;
	
};
```
Um diese Events abzufragen, wird die Funktion handleEvents in der Klasse Game erstellt.
In die Variable event wird später das abgefragte Event gespeichert.

```cpp
//Game.cpp
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
```

Mit SDL_PollEvent können die aktuellen Events abgefragt werden. Anschließend kann man das Event Objekt auslesen. In diesem Fall wird überprüft, ob das Event SDL_QUIT ausgelöst wurde.
Das Event SDL_QUIT wird bei dem Schließen des Fensters ausgelöst. In diesem Fall wird der Boolean isRunning auf false gesetzt, was zur Folge hat, dass das ganze Programm beendet wird.
Für die unterschiedlichen Eventtypen kann [hier](https://wiki.libsdl.org/SDL_EventType) nachgeschaut werden.

```cpp
//main.cpp
int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	while (game->isRunning)
	{
		game->handleEvents();  // <-- neu
		game->render();
	}
	game->clean();
	
	return 0;
}
```
Es soll mit jedem Schleifendurchlauf nach neuen Events geguckt werden.

## Dokumentation zu den hier verwendeten SDL2 Funktionen

[SDL_PollEvent](https://wiki.libsdl.org/SDL_PollEvent)



