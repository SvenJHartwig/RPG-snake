#include "gridController.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../commonFunctions.h"

using std::vector, std::string;

std::pair<int, int> RandomGeneratorImpl::getRandomPair(int max_value_x, int max_value_y, const std::set<std::pair<int, int>> &exclusions)
{
    indexToPair.clear();
    int index = 0;
    for (int i = 0; i < max_value_x; i++)
    {
        for (int j = 0; j < max_value_y; j++)
        {
            if (exclusions.find({i, j}) == exclusions.end())
            {
                indexToPair[index++] = {i, j};
            }
        }
    }
    if (indexToPair.size() == 0)
    {
        return {0, 0};
    }
    int randomIndex = (rand() % indexToPair.size()) - 1;
    return indexToPair[randomIndex];
}

int RandomGeneratorImpl::getRandom(int max_value)
{
    return (rand() % max_value) + 1;
}

GridController::GridController(IEatListener *eatListener)
{
    this->eatListener = eatListener;
    srand(time(NULL));
    rng = new RandomGeneratorImpl();
    food = new std::vector<Food *>(1, new Food());
    grid = new Grid();
    snake = new Snake();
}

GridController::~GridController()
{
}

void GridController::updateGrid()
{
    updateMobs();
    updateCollisionMap();
    checkCollisions();
    checkGameOver();
}

vector<vector<SEngine::Sprite> *> *GridController::getSpriteVector()
{
    using SEngine::Sprite;
    vector<vector<Sprite> *> *result = new vector<vector<Sprite> *>();
    // Level grid
    for (int yCoord = 0; yCoord < grid->getLevel()->size(); yCoord++)
    {
        vector<Sprite> *inner = new vector<Sprite>(grid->getLevel()->at(yCoord)->size());
        result->push_back(inner);
        for (int xCoord = 0; xCoord < grid->getLevel()->at(yCoord)->size(); xCoord++)
        {
            Sprite tempSprite = Sprite();
            if (dynamic_cast<Wall *>(grid->getLevel()->at(yCoord)->at(xCoord)))
            {
                tempSprite.texBaseX = 0.0f;
                tempSprite.texBaseY = 0.0f;
            }
            else if (dynamic_cast<Teleporter *>(grid->getLevel()->at(yCoord)->at(xCoord)))
            {
                tempSprite.texBaseX = 0.75f;
                tempSprite.texBaseY = 0.75f;
            }
            else
            {
                tempSprite.texBaseX = 0.25f;
                tempSprite.texBaseY = 0.0f;
            }
            result->at(yCoord)->at(xCoord) = tempSprite;
        }
    }
    // Dynamic elements
    for (int foodIndex = 0; foodIndex < food->size(); foodIndex++)
    {
        Food *f = food->at(foodIndex);
        Sprite temp = result->at(f->getPosY())->at(f->getPosX());
        if (foodIndex == 0)
        {
            temp.texBaseX = 0.0f;
            temp.texBaseY = 0.25f;
        }
        else
        {
            temp.texBaseX = 0.25f;
            temp.texBaseY = 0.25f;
        }
        result->at(f->getPosY())->at(f->getPosX()) = temp;
    }
    for (Mob *mob : *grid->getMobs())
    {
        Sprite temp = result->at(mob->getPosY())->at(mob->getPosX());
        temp.texBaseX = 0.5f;
        temp.texBaseY = 0.75f;
        result->at(mob->getPosY())->at(mob->getPosX()) = temp;
    }
    for (int snakeBodyIndex = 0; snakeBodyIndex < snake->getBody()->size(); snakeBodyIndex++)
    {
        SnakeBodyPart bodyPart = snake->getBody()->at(snakeBodyIndex);
        Sprite temp = result->at(bodyPart.getPosY())->at(bodyPart.getPosX());
        switch (bodyPart.facing)
        {
        case HORIZONTAL:
            temp.texBaseX = 0.5f;
            temp.texBaseY = 0.0f;
            break;
        case VERTICAL:
            temp.texBaseX = 0.75f;
            temp.texBaseY = 0.0f;
            break;
        case LEFT_TO_DOWN:
            temp.texBaseX = 0.0f;
            temp.texBaseY = 0.5f;
            break;
        case RIGHT_TO_DOWN:
            temp.texBaseX = 0.25f;
            temp.texBaseY = 0.75f;
            break;
        case LEFT_TO_UP:
            temp.texBaseX = 0.0f;
            temp.texBaseY = 0.75f;
            break;
        case RIGHT_TO_UP:
            temp.texBaseX = 0.25f;
            temp.texBaseY = 0.5f;
            break;
        }
        result->at(bodyPart.getPosY())->at(bodyPart.getPosX()) = temp;
    }
    Sprite temp = result->at(snake->getPosY())->at(snake->getPosX());
    switch (snake->facing)
    {
    case RIGHT:
        temp.texBaseX = 0.75f;
        temp.texBaseY = 0.25f;
        break;
    case LEFT:
        temp.texBaseX = 0.5f;
        temp.texBaseY = 0.25f;
        break;
    case DOWN:
        temp.texBaseX = 0.5f;
        temp.texBaseY = 0.5f;
        break;
    case UP:
        temp.texBaseX = 0.75f;
        temp.texBaseY = 0.5f;
        break;
    }
    result->at(snake->getPosY())->at(snake->getPosX()) = temp;

    return result;
}

void GridController::updateMobs()
{
    for (Mob *mob : *grid->getMobs())
    {
        mob->tick();
    }
    int newPos;
    for (Mob *mob : *grid->getMobs())
    {
        IntendedAction mobAction = mob->getIntendedAction();
        switch (mobAction)
        {
        case IntendedAction::MOVE_RIGHT:
            newPos = (mob->getPosX() + 1) % grid->getGridSizeX();
            if (!collisionOnPosition(newPos, mob->getPosY()))
            {
                mob->setPosX(newPos);
            }
            checkMobCollision(mob);
            break;
        case IntendedAction::MOVE_LEFT:
            newPos = mob->getPosX() - 1;
            if (newPos < 0)
            {
                newPos += grid->getGridSizeX();
            }
            if (!collisionOnPosition(newPos, mob->getPosY()))
            {
                mob->setPosX(newPos);
            }
            checkMobCollision(mob);
            break;
        case IntendedAction::MOVE_UP:
            newPos = mob->getPosY() - 1;
            if (newPos < 0)
            {
                newPos += grid->getGridSizeY();
            }
            if (!collisionOnPosition(mob->getPosX(), newPos))
            {
                mob->setPosY(newPos);
            }
            checkMobCollision(mob);
            break;
        case IntendedAction::MOVE_DOWN:
            newPos = (mob->getPosY() + 1) % grid->getGridSizeY();
            if (!collisionOnPosition(mob->getPosX(), newPos))
            {
                mob->setPosY(newPos);
            }
            checkMobCollision(mob);
            break;
        default:
            break;
        }
    }
}

void GridController::checkMobCollision(Mob *mob)
{
    if (anyMovedBodypartOnThisField(mob->getPosY(), mob->getPosX()) || mob->getPosX() == snake->getPosX() && mob->getPosY() == snake->getPosY())
    {
        snake->loseHealth(1);
        if (snake->getHealth() <= 0)
        {
            game_over = true;
        }
    }
}

void GridController::checkCollisions()
{
    int indexOfFoodOnThisField = returnFoodOnThisField(snake->getPosY(), snake->getPosX());
    if (indexOfFoodOnThisField != -1)
    {
        eatListener->eat(indexOfFoodOnThisField != 0);
        if (indexOfFoodOnThisField == 0)
        {
            snake->eat();
            std::set<std::pair<int, int>> exclusions = *(grid->occupiedSpacesWall);
            exclusions.insert(grid->occupiedSpacesSnake->begin(), grid->occupiedSpacesSnake->end());
            std::pair<int, int> newPair = rng->getRandomPair(grid->getGridSizeX(), grid->getGridSizeY(), exclusions);
            int newX = newPair.first;
            int newY = newPair.second;
            if (rng->getRandom(5) == 1)
            {
                std::pair<int, int> newSpecialPair = rng->getRandomPair(grid->getGridSizeX(), grid->getGridSizeY(), exclusions);
                int newSpecialX = newSpecialPair.first;
                int newSpecialY = newSpecialPair.second;
                generateNewSpecialFood(newSpecialX, newSpecialY);
            }
            generateNewFood(newX, newY);
        }
        else
        {
            food->erase(food->begin() + indexOfFoodOnThisField);
        }
    }
    grid->getLevel()->at(snake->getPosY())->at(snake->getPosX())->snakeOnElement(this);
    for (Mob *mob : *grid->getMobs())
    {
        if (mob->getPosX() == snake->getPosX() && mob->getPosY() == snake->getPosY())
        {
            mob->snakeOnElement(this);
        }
    }
}

void GridController::updateCollisionMap()
{
    grid->occupiedSpacesSnake->clear();
    grid->occupiedSpacesSnake->insert(std::pair<int, int>(snake->getPosX(), snake->getPosY()));
    for (SnakeBodyPart s : *(snake->getBody()))
    {
        grid->occupiedSpacesSnake->insert(std::pair<int, int>(s.getPosX(), s.getPosY()));
    }
}

bool GridController::collisionOnPosition(int x, int y)
{
    if (dynamic_cast<Wall *>(grid->getLevel()->at(y)->at(x)))
    {
        return true;
    }
    return false;
}

void GridController::checkGameOver()
{
    // If a wall or the snake's body is reached, game over
    if (dynamic_cast<Wall *>(grid->getLevel()->at(snake->getPosY())->at(snake->getPosX())))
    {
        game_over = true;
    }
    if (anyMovedBodypartOnThisField(snake->getPosY(), snake->getPosX()))
    {
        game_over = true;
    }
}

int GridController::returnFoodOnThisField(int posY, int posX)
{
    for (int foodIndex = 0; foodIndex < food->size(); foodIndex++)
    {
        if (posY == food->at(foodIndex)->getPosY() && posX == food->at(foodIndex)->getPosX())
        {
            return foodIndex;
        }
    }
    return -1;
}

bool GridController::anyMovedBodypartOnThisField(int posY, int posX)
{
    for (int k = 0; k < snake->getBody()->size(); k++)
    {
        if (snake->getBody()->at(k).getHasMoved() && posY == snake->getBody()->at(k).getPosY() && posX == snake->getBody()->at(k).getPosX())
        {
            return true;
        }
    }
    return false;
}

void GridController::moveSnakeRight()
{
    if (game_over)
    {
        return;
    }
    BodyPartFacing facing = HORIZONTAL;
    if (snake->getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake->getBody()->at(0);
        if (temp.getPosY() < snake->getPosY())
        {
            facing = RIGHT_TO_UP;
        }
        else if (temp.getPosY() > snake->getPosY())
        {
            facing = RIGHT_TO_DOWN;
        }
        else
        {
            facing = HORIZONTAL;
        }
    }
    moveSnakeBody(facing);
    snake->setPosX((snake->getPosX() + 1) % grid->getGridSizeX());
    snake->facing = RIGHT;
    while (snake->getPosX() < 0)
    {
        snake->setPosX(snake->getPosX() + grid->getGridSizeX());
    }
}

void GridController::moveSnakeLeft()
{
    if (game_over)
    {
        return;
    }
    BodyPartFacing facing = HORIZONTAL;
    if (snake->getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake->getBody()->at(0);
        if (temp.getPosY() < snake->getPosY())
        {
            facing = LEFT_TO_UP;
        }
        else if (temp.getPosY() > snake->getPosY())
        {
            facing = LEFT_TO_DOWN;
        }
        else
        {
            facing = HORIZONTAL;
        }
    }
    moveSnakeBody(facing);
    snake->setPosX((snake->getPosX() - 1) % grid->getGridSizeX());
    snake->facing = LEFT;
    while (snake->getPosX() < 0)
    {
        snake->setPosX(snake->getPosX() + grid->getGridSizeX());
    }
}

void GridController::moveSnakeUp()
{
    if (game_over)
    {
        return;
    }
    BodyPartFacing facing = VERTICAL;
    if (snake->getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake->getBody()->at(0);
        if (temp.getPosX() < snake->getPosX())
        {
            facing = LEFT_TO_UP;
        }
        else if (temp.getPosX() > snake->getPosX())
        {
            facing = RIGHT_TO_UP;
        }
        else
        {
            facing = VERTICAL;
        }
    }
    moveSnakeBody(facing);
    snake->setPosY((snake->getPosY() - 1) % grid->getGridSizeY());
    snake->facing = UP;
    while (snake->getPosY() < 0)
    {
        snake->setPosY(snake->getPosY() + grid->getGridSizeY());
    }
}

void GridController::moveSnakeDown()
{
    if (game_over)
    {
        return;
    }
    BodyPartFacing facing = VERTICAL;
    if (snake->getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake->getBody()->at(0);
        if (temp.getPosX() < snake->getPosX())
        {
            facing = LEFT_TO_DOWN;
        }
        else if (temp.getPosX() > snake->getPosX())
        {
            facing = RIGHT_TO_DOWN;
        }
        else
        {
            facing = VERTICAL;
        }
    }
    moveSnakeBody(facing);
    snake->setPosY((snake->getPosY() + 1) % grid->getGridSizeY());
    snake->facing = DOWN;
    while (snake->getPosY() < 0)
    {
        snake->setPosY(snake->getPosY() + grid->getGridSizeY());
    }
}

ISnake *GridController::getSnake()
{
    return snake;
}

bool GridController::isGameOver()
{
    return game_over;
}

void GridController::setRNG(RandomGenerator *rng)
{
    this->rng = rng;
}

void GridController::moveSnakeBody(BodyPartFacing facing)
{
    if (snake->getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake->getBody()->at(snake->getBody()->size() - 1);
        temp.setHasMoved(true);
        temp.facing = facing;
        temp.setPosX(snake->getPosX());
        temp.setPosY(snake->getPosY());
        snake->getBody()->pop_back();
        snake->getBody()->insert(snake->getBody()->begin(), temp);
    }
    for (int i = 1; i < food->size(); i++)
    {
        SpecialFood *special = static_cast<SpecialFood *>(food->at(i));
        special->decreaseTime();
        if (special->remainingTime() == 0)
        {
            food->erase(food->begin() + i);
        }
    }
}

void GridController::generateNewFood(int i, int j)
{
    food->at(0)->setPosX(i);
    food->at(0)->setPosY(j);
}

void GridController::generateNewSpecialFood(int i, int j)
{
    SpecialFood *newFood = new SpecialFood();
    newFood->setPosX(i);
    newFood->setPosY(j);
    food->push_back(newFood);
}

IGrid *GridController::getGrid()
{
    return grid;
}

std::vector<Food *> *GridController::getFood()
{
    return food;
}

void GridController::reset()
{
    food->clear();
    food->push_back(new Food());
    grid->reset();
    snake = new Snake();
    updateGrid();
    game_over = false;
}
void GridController::loadLevel(const string path)
{
    grid->loadFromFile(path);
}

void GridController::addMob(Mob *mob)
{
    grid->getMobs()->push_back(mob);
}
vector<Mob *> *GridController::getMobs()
{
    return grid->getMobs();
}