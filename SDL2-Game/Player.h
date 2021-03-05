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
    SDL_Texture* text;

    SDL_Rect position = {200,500,100,100};

    int delta = 0;
    float speed = 0.3;
    std::string expression_string = "0";

    bool toggle_input = false;

    float cur_angle = 0;

    Mix_Chunk* plasmaShot;
    

    Player(Game* instance);
    ~Player();

    void update(int delta);
    void checkInput(int delta);
    void render();
    void calculateFunction();

};

