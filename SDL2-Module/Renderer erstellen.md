---
layout: default
title: Renderer erstellen
parent: SDL2-Module
nav_order: 2
---

# Renderer erstellen

Um etwas in dem Fenster darstellen zu können wird ein Renderer benötigt.

```cpp
//Game.h
class Game
{
public:
	Game();
	~Game();
	void init(std::string title, int xpos, int ypos, int width, int height, int flags);
	void render(); // <-- neu
	void clean();

	SDL_Window* window;
	SDL_Renderer* renderer; // <-- neu
	bool isRunning;

	int window_w = 0;
	int window_h = 0;
	
};
```

Der Klasse Game wird also der Pointer renderer und die Funktion render hinzugefügt.


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
		renderer = SDL_CreateRenderer(window, -1, 0);				// <-- neu
		if (renderer)												// <-- neu
		{															// <-- neu
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	// <-- neu
			std::cout << "Renderer created" << std::endl;			// <-- neu
		}															// <-- neu
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}
```
Der Renderer muss ebenfalls initialsiert werden und benötigt zudem das erstellte Fenster.
Mit SDL_SetRenderDrawColor wird die Farbe eingestellt, mit der der Renderer zeichnet.
Die Zahlen in der Parameterliste stehen für einen RGBA-Farbwert.
In diesem Fall stellt das die Farbe weiß dar.

```cpp
//Game.cpp
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer); // <-- neu
	SDL_Quit();
	std::cout << "bye" << std::endl;
}
```
Auch der Renderer muss beim dem Beenden zerstört werden.

```cpp
//Game.cpp
void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent(renderer);
}
```
In der Funktion render wird zunächst mit SDL_RenderClear das Fenster aufgeräumt, indem das derzeitige Bild mit der aktuellen RenderColor übermalt wird.
Anschließend wird die Render-Farbe mit SDL_SetRenderDrawColor auf weiß zurückgesetzt. Mit SDL_RenderPresent wird das aktuelle Bild gerendert.
Weitere Renderfunktionen die im späteren Verlauf gezeigt werden, erstellen ein Bild nicht direkt auf dem Fenster, sondern schreiben diese Informationen in einen Buffer.
Mit SDL_RenderPresent werden diese Informationen aus dem Buffer ausgelesen und auf dem Fenster dargestellt. Aus diesem Grund sollte SDL_RenderPresent nur einmal pro Bildwiederholung und immer als letztes aufgerufen werden.

```cpp
//main.cpp
int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	while (game->isRunning)
	{
		game->render(); // <-- neu
	}
	game->clean();
	
	return 0;
}
```
In der Spielschleife wird jetzt die Funktion render einmal pro Schleifendurchlauf aufgerufen. Anders lässt sich auch sagen, dass pro Schleifendurchlauf ein Bild dargestellt wird.
Die Anzahl an Schleifendurchläufen pro Sekunde stellen damit die FPS dar. FPS ist ein häufig verwendeter Begriff bei Spielen und bedeutet: Frames per Second.

```cpp
//Game.cpp
void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);	// <-- neu
	SDL_Rect red_box = {0,0,500,500};					// <-- neu 
	SDL_RenderFillRect(renderer, &red_box);				// <-- neu
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent(renderer);
}
```
Mit der Funktion SDL_RenderFillRect kann ein Rechteck gezeichnet werden. In diesem Fall würde dieses Rechteck die Position 0,0 haben und 500\*500 Pixel groß sein.
Beim Ausführen sollte in dem Fenster ein rotes Rechteck zu sehen sein.
Dieses letzte Beispiel sollte nur zu Testzwecken verwendet werden.


## Dokumentation zu den hier verwendeten SDL2 Funktionen


[SDL_CreateRenderer](https://wiki.libsdl.org/SDL_CreateRenderer)

[SDL_SetRenderDrawColor](https://wiki.libsdl.org/SDL_SetRenderDrawColor)

[SDL_DestroyRenderer](https://wiki.libsdl.org/SDL_DestroyRenderer)

[SDL_Render_Clear](https://wiki.libsdl.org/SDL_RenderClear)

[SDL_RenderPresent](https://wiki.libsdl.org/SDL_RenderPresent)

[SDL_RenderFillRect](https://wiki.libsdl.org/SDL_RenderFillRect)


