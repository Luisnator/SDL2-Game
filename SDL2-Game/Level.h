#pragma once
#include "Gameobject.h"
#include <vector>
#include "Projectile.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Wall.h"
class Level : public Gameobject
{
public:
    Level(Game* instance);
    ~Level();

    void update(int delta);
    void render();

    void createGameobject(Gameobject* go);
    std::vector<Gameobject*> lvlObjects;
};

