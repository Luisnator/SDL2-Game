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
    float position[2] = {0,0};
    int delta = 0;
    float speed = 0.2;

    Player(Game* instance);
    ~Player();

    void update(int delta);
    void checkInput();
    void render();

};

