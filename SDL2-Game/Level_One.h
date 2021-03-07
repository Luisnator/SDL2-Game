#pragma once
#include "Level.h"
class Level_One :
    public Level
{
public:
    Level_One(Game* instance);
    ~Level_One();

    void update(int delta);
    void render();
};

