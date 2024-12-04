#pragma once

#include "../model/grid.h"
#include "iEatListener.h"
#include <string>
#include <set>
#include <map>

using std::string;

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

    void checkGameOver(Grid *grid);
    int returnFoodOnThisField(int i, int j);
    bool anyMovedBodypartOnThisField(int i, int j);
    bool anyBodypartOnThisField(int i, int j);
    void moveSnakeBody();

public:
    GridController(IEatListener *eatListener);
    ~GridController();
    vector<string> *updateGrid();
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
    void loadLevel(string path);
};
