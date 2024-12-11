#include "gridController.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>

using std::vector, std::string;

std::pair<int, int> RandomGeneratorImpl::getRandomPair(int max_value_x, int max_value_y, const std::set<std::pair<int, int>> &exclusions)
{

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
    int i = snake->getPosY();
    int j = snake->getPosX();
    int indexOfFoodOnThisField = returnFoodOnThisField(i, j);
    if (indexOfFoodOnThisField != -1)
    {
        eatListener->eat(indexOfFoodOnThisField != 0);
        if (indexOfFoodOnThisField == 0)
        {
            snake->eat();
            std::set<std::pair<int, int>> *exclusions = grid->occupiedSpacesWall;
            std::pair<int, int> newPair = rng->getRandomPair(grid->getGridSizeX(), grid->getGridSizeY(), *exclusions);
            int newX = newPair.first;
            int newY = newPair.second;
            if (rng->getRandom(5) == 1)
            {
                std::pair<int, int> newSpecialPair = rng->getRandomPair(grid->getGridSizeX(), grid->getGridSizeY(), *exclusions);
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
    checkGameOver(grid);
}

vector<vector<Sprite> *> *GridController::getSpriteVector()
{
    vector<vector<Sprite> *> *result = new vector<vector<Sprite> *>();
    // Level grid
    for (int i = 0; i < grid->getLevel()->size(); i++)
    {
        vector<Sprite> *inner = new vector<Sprite>();
        result->push_back(inner);
        for (int j = 0; j < grid->getLevel()->at(i).size(); j++)
        {
            Sprite tempSprite = Sprite();
            switch (grid->getLevel()->at(i)[j])
            {
            case 'W':
                tempSprite.texBaseX = 0.0f;
                tempSprite.texBaseY = 0.0f;
                break;
            default:
                tempSprite.texBaseX = 0.5f;
                tempSprite.texBaseY = 0.0f;
                break;
            }
            result->at(i)->push_back(tempSprite);
        }
    }
    // Dynamic elements
    for (int i = 0; i < food->size(); i++)
    {
        Food *f = food->at(i);
        Sprite temp = result->at(f->getPosY())->at(f->getPosX());
        temp.texBaseX = 0.0f;
        temp.texBaseY = 0.5f;
        result->at(f->getPosY())->at(f->getPosX()) = temp;
    }
    Sprite temp = result->at(snake->getPosY())->at(snake->getPosX());
    temp.texBaseX = 0.5f;
    temp.texBaseY = 0.5f;
    result->at(snake->getPosY())->at(snake->getPosX()) = temp;
    for (int i = 0; i < snake->getBody()->size(); i++)
    {
        SnakeBodyPart bodyPart = snake->getBody()->at(i);
        Sprite temp = result->at(bodyPart.getPosY())->at(bodyPart.getPosX());
        temp.texBaseX = 0.5f;
        temp.texBaseY = 0.5f;
        result->at(bodyPart.getPosY())->at(bodyPart.getPosX()) = temp;
    }

    return result;
}

void GridController::checkGameOver(Grid *grid)
{
    // If a wall or the snake's body is reached, game over
    int i = snake->getPosY();
    int j = snake->getPosX();
    if (grid->getLevel()->at(i)[j] == 'W')
    {
        game_over = true;
    }
    if (anyMovedBodypartOnThisField(i, j))
    {
        game_over = true;
    }
}

int GridController::returnFoodOnThisField(int i, int j)
{
    for (int k = 0; k < food->size(); k++)
    {
        if (i == food->at(k)->getPosY() && j == food->at(k)->getPosX())
        {
            return k;
        }
    }
    return -1;
}

bool GridController::anyMovedBodypartOnThisField(int i, int j)
{
    for (int k = 0; k < snake->getBody()->size(); k++)
    {
        if (snake->getBody()->at(k).getHasMoved() && i == snake->getBody()->at(k).getPosY() && j == snake->getBody()->at(k).getPosX())
        {
            return true;
        }
    }
    return false;
}

bool GridController::anyBodypartOnThisField(int i, int j)
{
    for (int k = 0; k < snake->getBody()->size(); k++)
    {
        if (i == snake->getBody()->at(k).getPosY() && j == snake->getBody()->at(k).getPosX())
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
    moveSnakeBody();
    snake->setPosX((snake->getPosX() + 1) % grid->getGridSizeX());
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
    moveSnakeBody();
    snake->setPosX((snake->getPosX() - 1) % grid->getGridSizeX());
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
    moveSnakeBody();
    snake->setPosY((snake->getPosY() - 1) % grid->getGridSizeY());
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
    moveSnakeBody();
    snake->setPosY((snake->getPosY() + 1) % grid->getGridSizeY());
    while (snake->getPosY() < 0)
    {
        snake->setPosY(snake->getPosY() + grid->getGridSizeY());
    }
}

Snake *GridController::getSnake()
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

void GridController::moveSnakeBody()
{
    if (snake->getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake->getBody()->at(snake->getBody()->size() - 1);
        temp.setHasMoved(true);
        temp.setPosX(snake->getPosX());
        temp.setPosY(snake->getPosY());
        snake->getBody()->pop_back();
        snake->getBody()->insert(snake->getBody()->begin(), temp);
    }
    for (int i = 1; i < food->size(); i++)
    {
        ((SpecialFood *)food->at(i))->decreaseTime();
        if (((SpecialFood *)food->at(i))->remainingTime() == 0)
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

Grid *GridController::getGrid()
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
vector<string> readFileAsStringArray(const string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        return {};
    }

    vector<string> lines;
    string line;

    // Read the file line by line and store each line in the vector
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return lines;
}
void GridController::loadLevel(const string path)
{
    grid->occupiedSpacesWall->clear();
    vector<string> level = readFileAsStringArray(path);
    grid->getLevel()->clear();
    for (int i = 0; i < level.size(); i++)
    {
        string l = level.at(i);
        grid->getLevel()->push_back(l);
        for (int j = 0; j < l.size(); j++)
        {
            if (l.at(j) == 'W')
                grid->occupiedSpacesWall->insert({j, i});
        }
    }
}