#pragma once

#include "../model/grid.h"

class RandomGenerator
{
public:
    virtual int getRandom(int max_value) = 0;
    virtual ~RandomGenerator() {};
};
class RandomGeneratorImpl : public RandomGenerator
{
public:
    int getRandom(int max_value) override;
};

class GridController
{
private:
    Snake snake;
    Food *food;
    bool game_over = false;
    RandomGenerator *rng;

    void checkGameOver(Grid *grid);
    bool anyFoodOnThisField(int i, int j);
    bool anyMovedBodypartOnThisField(int i, int j);
    bool anyBodypartOnThisField(int i, int j);
    void moveSnakeBody();

public:
    GridController();
    ~GridController();
    char **updateGrid(Grid *grid);
    void moveSnakeRight();
    void moveSnakeLeft();
    void moveSnakeUp();
    void moveSnakeDown();
    Snake *getSnake();
    bool isGameOver();
    void setRNG(RandomGenerator *rng);
};
