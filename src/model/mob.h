#pragma once

#include "gridElement.h"

enum class IntendedAction
{
    NONE,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN
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
    void serialize(std::ofstream *outFile) override;
    void tick();
    Enemy(int pos_x, int pos_y);
    ~Enemy();
};