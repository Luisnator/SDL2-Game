#pragma once
#include "Gameobject.h"
#include "SDL_image.h"
#include <iostream>
#include "Sprite.h"
#include "SDL_mixer.h"
#include "Laserbarrier.h"
#include "TextRender.h"

class Player :
    public Gameobject
{
public:
    Sprite* sprite;
    TextRender* tr;

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
    bool checkCollision();

};

