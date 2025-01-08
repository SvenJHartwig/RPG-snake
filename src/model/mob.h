#pragma once

#include "grid.h"

class Mob : public GridElement
{
};

class Enemy : public Mob
{
private:
public:
    Enemy(int pos_x, int pos_y);
    ~Enemy();
}