#pragma once

#include "../model/grid.h"
#include "iEatListener.h"

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
    std::vector<Food> *food;
    bool game_over = false;
    RandomGenerator *rng;
    Grid *grid;
    IEatListener *eatListener;

    void checkGameOver(Grid *grid);
    bool anyFoodOnThisField(int i, int j);
    bool anyMovedBodypartOnThisField(int i, int j);
    bool anyBodypartOnThisField(int i, int j);
    void moveSnakeBody();

public:
    GridController(IEatListener *eatListener);
    ~GridController();
    char **updateGrid();
    void moveSnakeRight();
    void moveSnakeLeft();
    void moveSnakeUp();
    void moveSnakeDown();
    Snake *getSnake();
    bool isGameOver();
    void setRNG(RandomGenerator *rng);
    void generateNewFood(int i, int j);
    Grid *getGrid();
};
