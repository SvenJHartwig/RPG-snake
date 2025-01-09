#pragma once

#include "grid.h"

class Mob : public GridElement
{
public:
    virtual void tick() = 0;
};

class Enemy : public Mob
{
private:
public:
    void tick();
    Enemy(int pos_x, int pos_y);
    ~Enemy();
};