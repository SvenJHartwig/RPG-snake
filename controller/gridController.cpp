#include "gridController.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

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

    vector<string> *chars = grid->getGrid();

    for (int i = 0; i < grid_size_y; i++)
    {
        string temp(grid_size_y, 'x');
        chars->push_back(temp);
        for (int j = 0; j < grid_size_x; j++)
        {
            if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1)
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
                        int newX = rng->getRandom(grid->getGridSizeX() - 2);
                        int newY = rng->getRandom(grid->getGridSizeY() - 2);
                        if (rng->getRandom(5) == 1)
                        {
                            int newSpecialX = rng->getRandom(grid->getGridSizeX() - 2);
                            int newSpecialY = rng->getRandom(grid->getGridSizeY() - 2);
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
    grid->setGrid(chars);
    return chars;
}

void GridController::checkGameOver(Grid *grid)
{
    // If a wall or the snake's body is reached, game over
    int i = snake->getHeadY();
    int j = snake->getHeadX();
    if (i == 0 || i == grid->getGridSizeY() - 1 || j == 0 || j == grid->getGridSizeX() - 1)
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
    snake->setPosX(snake->getHeadX() + 1);
}

void GridController::moveSnakeLeft()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake->setPosX(snake->getHeadX() - 1);
}

void GridController::moveSnakeUp()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake->setPosY(snake->getHeadY() - 1);
}

void GridController::moveSnakeDown()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake->setPosY(snake->getHeadY() + 1);
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
    grid->setGrid(new vector<string>());
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
    vector<string> level = readFileAsStringArray(path);
    grid->setLevel(&level);
}
