#pragma once
#include "Level.h"
class Level_One :
    public Level
{
public:
    Level_One(Game* instance);
    ~Level_One();

    Sprite* one_star;
    Sprite* two_star;
    Sprite* three_star;

    Player* player;

    Mix_Music* m_background;

    TextRender* popup_text_r;
    TextRender* popup_text_c;

    void update(int delta);
    void render();

    bool allEnemiesDead();
};

