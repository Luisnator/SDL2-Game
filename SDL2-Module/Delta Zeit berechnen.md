---
layout: default
title: Delta Zeit berechnen
parent: SDL2-Module
nav_order: 6
---

# Delta Zeit berechnen

Die Delta Zeit die berechnet wird stellt hier die Zeit zwischen den Aufrufen der Funktion update dar.

```cpp
//Game.cpp
void Game::GameLoop()
{
	int tickstart = SDL_GetTicks(); 		// <-- neu
	int tickend = SDL_GetTicks();			// <-- neu
	while (loop)
	{
		int delta = tickend - tickstart;	// <-- neu
		handleEvents();
		tickstart = SDL_GetTicks();			// <-- neu
		update(delta);						// <-- angepasst
		render();
		tickend = SDL_GetTicks();			// <-- neu
	}
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


