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
    Sprite* sprite;

    int position[2] = {0,0};
    float width = 100;
    float height = 100;
    int delta = 0;
    float speed = 0.3;
    std::string expression_string;

    float cur_angle = 0;

    Mix_Chunk* plasmaShot;
    

    Player(Game* instance);
    ~Player();

    void update(int delta);
    void checkInput(int delta);
    void render();
    void calculateFunction();

};

