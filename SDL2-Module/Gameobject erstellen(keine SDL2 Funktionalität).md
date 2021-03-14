---
layout: default
title: Gameobject erstellen(keine SDL2 Funktionalität)
parent: SDL2-Module
nav_order: 4
---

# Gameobject erstellen

Die Klasse Gameobject soll die Basisklasse für alle Entitäten im Spiel werden. Die Klasse Gameobject soll selber nie direkt instanziiert werden.

```cpp
//Gameobject.h
class Gameobject
{
public:
	Gameobject(Game* instance);
	virtual ~Gameobject();

	Game* instance;
	std::string type;

	SDL_Rect position = {0,0,0,0};

	virtual void update(int delta);
	virtual void render();

};
```
Die alle Klassen die von Gameobject erben, sollen eine Referenz zu dem ihnen zugehörigen Spiel haben, weshalb die Klasse eine Referenz zu der Klasse Game besitzt.
Der Destruktor ist mit virtual gekennzeichnet, da später Objekte über die Gameobject-Referenz gelöscht werden und dennoch der Destruktor der Kind-Klasse aufgerufen werden soll.
In den String type wird von den Kind-Klassen ihr Klassenname eingetragen, um später Zugehörigkeiten erkennen zu können. In diesem Spiel sind alle Objekte Rechtecke, weshalb die Position und Maße mit
 einem SDL_Rect-Objekt names position festgehalten wird. Die Funktionen update und render sollen später jeweils einmal pro Bildwiederholung aufgerufen werden. Da auch diese Funktionen über die Gameobject-Referenz
 aufgerufen werden, müssen diese mit virtual gekennzeichnet sein. In den Parameter delta der Funktion update wird später die Zeit übergeben, die seit der letzten Bildwiederholung vergangen ist.
 In der Funktion update sollen alle logischen Operationen die nichts direkt mit dem Darstellen des Bildes zu tun haben getätigt werden. 
```cpp
//Gameobject.cpp
Gameobject::Gameobject(Game* instance)
{
	this->instance = instance;
}

Gameobject::~Gameobject()
{
}

void Gameobject::update(int delta)
{
}

void Gameobject::render()
{
}
```
Da die Klasse Gameobject wie bereits erwähnt kein eigenes Verhalten besitzt, ist die Implementation erwartungsgemäß nicht sehr kompliziert.

```cpp
//Game.h
class Game
{
public:
	Game();
	~Game();
	void init(std::string title, int xpos, int ypos, int width, int height, int flags);
	void handleEvents();
	void update(int delta); // <-- neu
	void render();
	void clean();
	void registerGameobject(Gameobject* go); // <-- neu
	void unregisterGameobject(Gameobject* go); // <-- neu
	std::vector<Gameobject*> getGameobjects(); // <-- neu

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Gameobject*> gameobjects; // <-- neu
	SDL_Event event;
	bool isRunning;

	int window_w = 0;
	int window_h = 0;
	
};
```
Die Klasse Game wird um diverse Funktionen und Variablen erweitert. Die Klasse Game erhält einen Liste mit Referenzen zu Gameobject-Objekten. 
Mit den Funktionen registerGameobject und unregisterGameobject können Gameobject-Objekte zu der Liste hinzugefügt oder rausgelöscht werden.
Mit der Funktion getGameobjects wird die Liste der Gameobject-Objekte zurückgegeben. 
Zudem erhält die Klasse Game auch die Funktion update.  

```cpp
//Game.cpp
void Game::update(int delta)
{
	for (int i = 0; i < gameobjects.size(); i++)
	{
		gameobjects[i]->update(delta);
	}
}	
};
```
In der Funktion update der Klasse Game wird jetzt von jedem Gameobject in der Gameobject-Liste, die Funktion update aufgerufen.
Also wenn die Funktion update eines Game-Objektes aufgerufen wird, dann werden auch von jedem diesem Spiel zugehörigen Gameobject-Objekt die Funktion update aufgerufen.

```cpp
//Game.cpp
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
```
Das Gleiche gilt auch für die Funktion render.

```cpp
//Game.cpp
void Game::registerGameobject(Gameobject* go)
{
	gameobjects.push_back(go);
}
```
Die Funktion registerGameobject fügt das übergebene Objekt der Gameobject-Liste hinzu.

```cpp
//Game.cpp
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
```
Die Funktion unregisterGameobject probiert das per Parameter übergebene Objekt in der Gameobject-Liste zu finden und dann rauszulöschen. 

```cpp
//main.cpp
int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	while (game->isRunning)
	{
		game->handleEvents();
		game->update(0); // <-- neu
		game->render();
	}
	game->clean();
	
	return 0;
}
```
Im letzten Schritt wird die Funktion update auch in der Spielschleife aufgerufen, damit jedes Gameobject-Objekt pro Bildwiederholung etwas tun kann.
Die Funktion update erhält Platzhalterweise den Wert 0 für den Parameter delta.
