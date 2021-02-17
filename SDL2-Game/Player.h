#pragma once
#include "Gameobject.h"
#include "SDL_image.h"
#include <iostream>
#include "Sprite.h"

class Player :
    public Gameobject
{
public:
    SDL_Texture* playerTex;
    Sprite* sprite;
    
    Player(Game* instance);
    ~Player();

    void update(int delta);

    void render();

};

