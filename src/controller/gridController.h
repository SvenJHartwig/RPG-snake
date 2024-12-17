#pragma once

#include "../model/grid.h"
#include "../model/snake.h"
#include "../view/engine/elements/spriteGrid.h"
#include "iEatListener.h"
#include <string>
#include <set>
#include <map>

class RandomGenerator
{
public:
    virtual std::pair<int, int> getRandomPair(int max_value_x, int max_value_y, const std::set<std::pair<int, int>> &exclusions) = 0;
    virtual int getRandom(int max_value) = 0;
    virtual ~RandomGenerator() {};
};
class RandomGeneratorImpl : public RandomGenerator
{
private:
    std::map<int, std::pair<int, int>> indexToPair;

public:
    std::pair<int, int> getRandomPair(int max_value_x, int max_value_y, const std::set<std::pair<int, int>> &exclusions) override;
    int getRandom(int max_value) override;
};

class GridController
{
private:
    Snake *snake;
    std::vector<Food *> *food;
    bool game_over = false;
    RandomGenerator *rng;
    Grid *grid;
    IEatListener *eatListener;

    void checkOnFood();
    void updateCollisionMap();
    void checkGameOver();
    int returnFoodOnThisField(int i, int j);
    bool anyMovedBodypartOnThisField(int i, int j);
    void moveSnakeBody(BodyPartFacing facing);

public:
    GridController(IEatListener *eatListener);
    ~GridController();
    void updateGrid();
    void moveSnakeRight();
    void moveSnakeLeft();
    void moveSnakeUp();
    void moveSnakeDown();
    Snake *getSnake();
    bool isGameOver();
    void setRNG(RandomGenerator *rng);
    void generateNewFood(int i, int j);
    void generateNewSpecialFood(int i, int j);
    Grid *getGrid();
    std::vector<Food *> *getFood();
    void reset();
    void loadLevel(std::string path);
    std::vector<std::vector<SEngine::Sprite> *> *getSpriteVector();
};
