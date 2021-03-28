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
	void GameLoop();
	void render();
	void clean();
	void handleEvents(); // <-- neu

	SDL_Window* window;
	SDL_Renderer* renderer;
    SDL_Event event; // <-- neu
	bool loop;

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
	switch (event.type) 
	{
	case SDL_QUIT:
		loop = false;
		break;
	default:
		break;
	}
}
```

Mit SDL_PollEvent können die aktuellen Events abgefragt werden. Anschließend kann man das Event Objekt auslesen. In diesem Fall wird überprüft, ob das Event SDL_QUIT ausgelöst wurde.
Das Event SDL_QUIT wird bei dem Schließen des Fensters ausgelöst. In diesem Fall wird der Boolean loop auf false gesetzt, was zur Folge hat, dass das ganze Programm beendet wird.
Für die unterschiedlichen Eventtypen kann [hier](https://wiki.libsdl.org/SDL_EventType) nachgeschaut werden.

```cpp
//Game.cpp
void Game::GameLoop()
{
	while (loop)
	{
		handleEvents();
		render();
	}
}
```
Es soll mit jedem Schleifendurchlauf nach neuen Events geguckt werden.

## Dokumentation zu den hier verwendeten SDL2 Funktionen

[SDL_PollEvent](https://wiki.libsdl.org/SDL_PollEvent)



