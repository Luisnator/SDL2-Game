#pragma once
#include "Level.h"
#include "Level_One.h"
class Level_Two :
    public Level
{
public:
    Level_Two(Game* instance);
    ~Level_Two();

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

