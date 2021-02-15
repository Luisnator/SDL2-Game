#pragma once
#include "Gameobject.h"
#include "SDL_image.h"
#include <iostream>

class Player :
    public Gameobject
{
public:
    SDL_Texture* playerTex;
    
    Player(Game* instance);
    ~Player();

    void update(int delta);

    void render();

};

