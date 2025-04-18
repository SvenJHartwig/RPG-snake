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
    int id = 0;
    int ticksSinceLastMovement = 0;

public:
    static int currentId;
    void snakeOnElement(IGridController *controller) override;
    void setTicksSinceLastMovement(int ticksSinceLastMovement);
    void serialize(std::ofstream *outFile) override;
    void tick() override;
    Enemy(int pos_x, int pos_y);
    ~Enemy();
};