#pragma once
#include "Gameobject.h"
#include "Sprite.h"
#include <vector>
#include "Game.h"
#include "SDL_mixer.h"
class Enemy :
    public Gameobject
{
public:
    Enemy(SDL_Rect position, Game* instance);
    ~Enemy();

    Sprite* sprite;
    Mix_Chunk* m_screech;

    bool dead = false;

    void update(int delta);
    void render();
    void screech();
};

