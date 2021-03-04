#pragma once
#include "Gameobject.h"
#include "Sprite.h"
#include "Game.h"
class Wall :
    public Gameobject
{
public:
    Wall(SDL_Rect position, Game* instance);
    ~Wall();

    Sprite* sprite;
    SDL_Rect position = { 0,0,0,0 };
    
    void update(int delta);
    void render();
};

