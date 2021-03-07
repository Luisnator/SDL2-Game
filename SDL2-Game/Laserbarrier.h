#pragma once
#include "Gameobject.h"
#include "Sprite.h"

class Laserbarrier :
    public Gameobject
{
public:
    Laserbarrier(SDL_Rect position, Game* instance);
    ~Laserbarrier();

    Sprite* sprite;

    void update(int delta);
    void render();

};

