---
layout: default
title: Hintergrundbild rendern
parent: SDL2-Module
nav_order: 5
---

# Hintergrundbild rendern

*Für dieses Kapitel ist es nötig [SDL_image](https://www.libsdl.org/projects/SDL_image/) installiert zu haben.*

Mit der SDL_image Bibliothek ist es möglich Bilder in Form von SDL_Texturen zu speichern.

```cpp
//TextureLoader.h
class TextureLoader
{
public:
	static SDL_Texture* loadTextureFromImage(std::string path,SDL_Renderer* renderer,int flags = IMG_INIT_PNG);
};
```
Da Texturen vorraussichtlich öfters geladen werden müssen, wird hier eine statische Funktion für die Klasse TextureLoader deklariert.
In den Parameter path soll ein Pfad zu der Bilddatei eingetragen werden. Bei dem Parameter renderer soll der aktuelle Renderer des Spiels eingetragen werden.
Bei dem Parameter flags kann ein Flag für die Art der Bilddatei gesetzt werden, hier wird standardmäßig von einer PNG-Datei ausgegangen. 
Weitere Flags lassen sich [hier](https://www.libsdl.org/projects/SDL_image/docs/SDL_image_8.html) finden.

```cpp
//TextureLoader.cpp
SDL_Texture* TextureLoader::loadTextureFromImage(std::string path,SDL_Renderer* renderer,int flags)
{
    SDL_Texture* texture = nullptr;
    IMG_Init(flags);
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Can't load image from path: " << path << "IMG_Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            std::cout << "Cant create texture Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}
```
Mit IMG_Init wird die Unterstützung für den gewollten Dateityp gewährleistet. Anschließend wird über die Funktion IMG_Load ein SDL_Surface geladen. 
Ein SDL_Surface besitzt alle Informationen über das Bild, kann aber noch nicht vom Renderer auf dem Fenster dargestellt werden. 
Deswegen muss mit dem geladenen SDL_Surface noch ein SDL_Texture mit der Funktion SDL_CreateTextureFromSurface erstellt werden.
Da nur die SDL_Texture benötigt wird, sollte das SDL_Surface vor dem Aufruf des return-Statements gelöscht werden.
Eine genauere Erklärung zu dem Unterschied zwischen einem SDL_Surface und einer SDL_Texture kann [hier](https://stackoverflow.com/questions/21392755/difference-between-surface-and-texture-sdl-general) gefunden werden.

```cpp
//Background.h
class Background : public Gameobject
{
public:
	Background(std::string path,Game* instance);
	~Background();
	SDL_Texture* image;
	void update(int delta);
	void render();
};
```
Jetzt wo es möglich ist Texturen zu laden, ist es angebracht dies auch zu nutzen. Die Klasse Background ist nur dafür dar ein statisches Bild über das ganze Fenster hinweg zu rendern.
Es fällt zudem auf, dass die Klasse Background von der Klasse Gameobject erbt. Dies hat zur Folge, dass die Klasse Background die Funktionen update und render implementieren muss.

```cpp
//Background.cpp
Background::Background(std::string path, Game* instance) : Gameobject(instance)
{
	image = TextureLoader::loadTextureFromImage(path, instance->renderer);
	type = "Background";
}

Background::~Background()
{
	SDL_DestroyTexture(image);
}

void Background::update(int delta)
{
}

void Background::render()
{
	SDL_RenderCopy(instance->renderer, image, NULL, NULL);
}
```
Die Komplexität der Implementation von den Klassenfunktionen ist überschaubar. Im Konstruktor wird das Bild mithilfe der erstellten TextureLoader Klasse geladen und gespeichert.
Zudem wird der Name der Klasse in die Variable type gespeichert. 
Im Destruktor wird sichergestellt, dass der Speicher für die Textur freigegeben wird. Da der Hintergrund kein aktives Verhalten haben soll, befindet sich kein Code in der Funktion update.
In der Funktion render wird mit SDL_RenderCopy das Bild in den Render-Buffer geschrieben. Beim ersten Parameter muss ein Renderer angegeben werden. Der Zweite Parameter ist die Textur die gerendert werden soll.
Mit dem dritten Parameter kann man bestimmen, ob nur ein bestimmter Bereich der Textur gerendert werden soll. Bei NULL wird die ganze Textur gerendert. Der vierte Parameter bestimmt wo und wie groß die Textur gerendert werden soll.
Bei NULL wird die Textur über das ganze Fenster gerendert. 
Die letzten beiden Parameter werden nochmal genauer bei dem Kapitel Sprites betrachtet.

```cpp
//main.cpp
int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->init("Cooles Spiel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	game->registerGameobject(new Background("../assets/urban-landscape-background.png", instance)); // <-- neu
	game->GameLoop();
	game->clean();
	
	return 0;
}
```

In der main-Funktion kann dieses Objekt im Spiel registriert werden und wird jetzt mit jedem Spielschleifendurchlauf mitgerendert. 

## Dokumentation zu den hier verwendeten SDL2 Funktionen

[IMG_Init](https://www.libsdl.org/projects/SDL_image/docs/SDL_image_8.html)

[IMG_Load](https://www.libsdl.org/projects/SDL_image/docs/SDL_image_11.html)

[SDL_CreateTextureFromSurface](https://wiki.libsdl.org/SDL_CreateTextureFromSurface)

[SDL_FreeSurface](https://wiki.libsdl.org/SDL_FreeSurface)

[SDL_DestroyTexture](https://wiki.libsdl.org/SDL_DestroyTexture)

[SDL_RenderCopy](https://wiki.libsdl.org/SDL_RenderCopy)

