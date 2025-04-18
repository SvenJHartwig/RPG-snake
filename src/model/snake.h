#pragma once

#include "gridElement.h"
#include <vector>

class Food : public GridElement
{
public:
    void snakeOnElement(IGridController *controller) override;
    void serialize(std::ofstream *outFile) override;
    Food();
    ~Food();
};

class SpecialFood : public Food
{
private:
    int remainingMoves = 0;

public:
    void snakeOnElement(IGridController *controller) override;
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
    void snakeOnElement(IGridController *controller) override;
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

class Snake : public GridElement, public ISnake
{
private:
    int maxHealth = 3;
    int health = 3;
    std::vector<SnakeBodyPart> body;

public:
    void snakeOnElement(IGridController *controller) override;
    void serialize(std::ofstream *outFile) override;
    Facing facing = RIGHT;
    Snake();
    ~Snake();
    void eat() override;
    std::vector<SnakeBodyPart> *getBody();
    void loseHealth(int health);
    int getHealth() override;
    int getPosX() override;
    int getPosY() override;
    void setPosX(int pos) override;
    void setPosY(int pos) override;
};
