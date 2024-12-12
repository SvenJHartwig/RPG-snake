#pragma once

#include "grid.h"
#include <vector>

class Food : public GridElement
{

public:
    Food();
    ~Food();
};

class SpecialFood : public Food
{
private:
    int remainingMoves = 0;

public:
    SpecialFood() { remainingMoves = 20; }
    int remainingTime() { return remainingMoves; }
    void decreaseTime() { remainingMoves--; }
};
class SnakeBodyPart : public GridElement
{
private:
    bool has_moved = false;

public:
    SnakeBodyPart(int pos_x, int pos_y);
    ~SnakeBodyPart();
    bool getHasMoved();
    void setHasMoved(bool val);
};

enum Facing
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Snake : public GridElement
{
private:
    std::vector<SnakeBodyPart> body;

public:
    Facing facing = RIGHT;
    Snake();
    ~Snake();
    void eat();
    std::vector<SnakeBodyPart> *getBody();
};
