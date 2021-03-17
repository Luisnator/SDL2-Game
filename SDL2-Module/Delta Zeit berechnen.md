---
layout: default
title: Delta Zeit berechnen
parent: SDL2-Module
nav_order: 6
---

# Delta Zeit berechnen

Die Delta Zeit die berechnet wird stellt hier die Zeit zwischen den Aufrufen der Funktion update dar.

```cpp
//main.cpp
int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	int tickstart = SDL_GetTicks(); // <-- neu
	int tickend = SDL_GetTicks(); // <-- neu
	game->registerGameobbject(new Background("../assets/urban-landscape-background.png", instance));
	while (game->isRunning)
	{
		int delta = tickend - tickstart; // <-- neu
		game->handleEvents();
		tickstart = SDL_GetTicks(); // <-- neu
		game->update(delta); // <-- angepasst
		game->render();
		tickend = SDL_GetTicks(); // <-- neu
	}
	game->clean();
	
	return 0;
}
```
Die Funktion SDL_GetTicks gibt die Anzahl an Millisekunden zurück die seit der Initalisierung von SDL2 vergangen sind.
Somit kann man die Zeit vor dem Aufruf und die Zeit nach dem Aufruf von der Funktion update nehmen und daraus die Differenz bilden. 
Die Differenz stellt dann die gewollte Delta Zeit dar. Die Delta Zeit ist zum Beispiel für flüssige Bewegungen bei schwankender Framerate wichtig.
Wenn man eine konstante Framerate hätte wäre die Delta Zeit nicht nötig. Manche Spiele begrenzen die Framerate manuell, um beispielsweise Bewegung auf Basis der Framerate zu berechnen anstatt auf Basis der Delta Zeit.
Allerdings ist es riskant wichtige Berechnungen wie zum Beispiel Physikberechnungen abhängig von der Framerate zu berechnen, da es nur möglich ist die Framerate nach oben hin zu begrenzen aber nicht nach unten.
Schlechte Hardware kann im schlimmsten Fall die gewollte Framerate nicht erreichen und selbst dann sollte das Spiel noch korrekt funktionieren.


## Dokumentation zu den hier verwendeten SDL2 Funktionen

[SDL_GetTicks](https://wiki.libsdl.org/SDL_GetTicks)


