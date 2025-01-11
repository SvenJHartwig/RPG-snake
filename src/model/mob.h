#pragma once

#include "grid.h"

enum class IntendedAction
{
    NONE,
    MOVE_RIGHT
};

class Mob : public GridElement
{
protected:
    IntendedAction intendedAction = IntendedAction::NONE;

public:
    IntendedAction getIntendedAction();
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