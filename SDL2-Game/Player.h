#pragma once
#include "Gameobject.h"
#include "SDL_image.h"
#include <iostream>
#include "Sprite.h"
#include "SDL_mixer.h"

class Player :
    public Gameobject
{
public:
    SDL_Texture* playerTex;
    Sprite* sprite;

    int position[2] = {0,0};
    float width = 100;
    float hight = 100;
    int delta = 0;
    float speed = 0.2;

    Mix_Chunk* punchSound;
    

    Player(Game* instance);
    ~Player();

    void update(int delta);
    void checkInput();
    void render();
    void calculateFunction();

};

