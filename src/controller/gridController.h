#pragma once

#include "../model/grid.h"
#include "../model/mob.h"
#include "../model/snake.h"
#include "../model/winCondition.h"
#include "../view/engine/elements/spriteGrid.h"
#include "iEatListener.h"
#include "iGridController.h"
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

class GridController : public IGridController
{
private:
    Snake *snake;
    std::vector<Food *> *food;
    bool game_over = false;
    RandomGenerator *rng;
    Grid *grid;
    IEatListener *eatListener;
    std::vector<Teleporter *> *teleporters;

    void updateMobs();
    void updateCollisionMap();
    void checkCollisions();
    void checkGameOver();
    int returnFoodOnThisField(int i, int j);
    bool anyMovedBodypartOnThisField(int i, int j);
    void moveSnakeBody(BodyPartFacing facing);
    bool collisionOnPosition(int x, int y);

public:
    GridController(IEatListener *eatListener);
    ~GridController();
    void updateGrid();
    void moveSnakeRight();
    void moveSnakeLeft();
    void moveSnakeUp();
    void moveSnakeDown();
    bool isGameOver();
    void setRNG(RandomGenerator *rng);
    void generateNewFood(int i, int j);
    void generateNewSpecialFood(int i, int j);
    void reset();
    void loadLevel(std::string path) override;
    Grid *getGrid();
    std::vector<Food *> *getFood();
    Snake *getSnake();
    std::vector<std::vector<SEngine::Sprite> *> *getSpriteVector();
    void addMob(Mob *mob);
    std::vector<Mob *> *getMobs();
};
