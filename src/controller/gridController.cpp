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

vector<string> *GridController::updateGrid()
{
    int grid_size_x = grid->getGridSizeX();
    int grid_size_y = grid->getGridSizeY();

    vector<string> *level = grid->getLevel();
    vector<string> *chars = grid->getGrid();

    if (chars->size() == 0)
    {
        for (int i = 0; i < grid_size_y; i++)
        {
            string temp(grid_size_y, 'x');
            chars->push_back(temp);
        }
    }

    for (int i = 0; i < grid_size_y; i++)
    {
        for (int j = 0; j < grid_size_x; j++)
        {
            if (level->size() != 0 && level->at(i)[j] == 'W')
            {
                // Wall
                chars->at(i)[j] = 'W';
            }
            else if (i == snake->getHeadY() && j == snake->getHeadX())
            {
                // Snake
                chars->at(i)[j] = 'H';
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
            }
            else if (anyBodypartOnThisField(i, j))
            {
                // Snake Body
                chars->at(i)[j] = 'B';
            }
            else if (returnFoodOnThisField(i, j) == 0)
            {
                // Normal food
                chars->at(i)[j] = 'F';
            }
            else if (returnFoodOnThisField(i, j) > 0)
            {
                // Special food
                chars->at(i)[j] = 'S';
            }
            else
            {
                // Grid floor
                chars->at(i)[j] = 'x';
            }
        }
    }
    // Update food position, since this could've changed during the loop
    for (int i = 0; i < food->size(); i++)
    {
        if (chars->at(food->at(i)->getPosY())[food->at(i)->getPosX()] != 'B')
        {
            if (i == 0)
            {
                chars->at(food->at(i)->getPosY())[food->at(i)->getPosX()] = 'F';
            }
            else
            {
                chars->at(food->at(i)->getPosY())[food->at(i)->getPosX()] = 'S';
            }
        }
    }
    checkGameOver(grid);
    return chars;
}

void GridController::checkGameOver(Grid *grid)
{
    // If a wall or the snake's body is reached, game over
    int i = snake->getHeadY();
    int j = snake->getHeadX();
    if (grid->getGrid()->at(i)[j] == 'W')
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
    snake->setPosX((snake->getHeadX() + 1) % grid->getGridSizeX());
    while (snake->getHeadX() < 0)
    {
        snake->setPosX(snake->getHeadX() + grid->getGridSizeX());
    }
}

void GridController::moveSnakeLeft()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake->setPosX((snake->getHeadX() - 1) % grid->getGridSizeX());
    while (snake->getHeadX() < 0)
    {
        snake->setPosX(snake->getHeadX() + grid->getGridSizeX());
    }
}

void GridController::moveSnakeUp()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake->setPosY((snake->getHeadY() - 1) % grid->getGridSizeY());
    while (snake->getHeadY() < 0)
    {
        snake->setPosY(snake->getHeadY() + grid->getGridSizeY());
    }
}

void GridController::moveSnakeDown()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake->setPosY((snake->getHeadY() + 1) % grid->getGridSizeY());
    while (snake->getHeadY() < 0)
    {
        snake->setPosY(snake->getHeadY() + grid->getGridSizeY());
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
        temp.setPosX(snake->getHeadX());
        temp.setPosY(snake->getHeadY());
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