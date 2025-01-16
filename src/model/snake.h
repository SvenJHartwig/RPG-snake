#pragma once

#include "grid.h"
#include <vector>

class Food : public GridElement
{

public:
    void serialize(std::ofstream *outFile) override;
    Food();
    ~Food();
};

class SpecialFood : public Food
{
private:
    int remainingMoves = 0;

public:
    void serialize(std::ofstream *outFile) override;
    SpecialFood() { remainingMoves = 20; }
    int remainingTime() { return remainingMoves; }
    void decreaseTime() { remainingMoves--; }
};

enum BodyPartFacing
{
    HORIZONTAL,
    VERTICAL,
    LEFT_TO_DOWN,
    RIGHT_TO_DOWN,
    LEFT_TO_UP,
    RIGHT_TO_UP
};

class SnakeBodyPart : public GridElement
{
private:
    bool has_moved = false;

public:
    void serialize(std::ofstream *outFile) override;
    BodyPartFacing facing = HORIZONTAL;
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
    void serialize(std::ofstream *outFile) override;
    Facing facing = RIGHT;
    Snake();
    ~Snake();
    void eat();
    std::vector<SnakeBodyPart> *getBody();
};
