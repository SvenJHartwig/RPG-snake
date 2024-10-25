#include "gridController.h"
#include <cstdlib>
#include <time.h>

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

char **GridController::updateGrid()
{
    int grid_size_x = grid->getGridSizeX();
    int grid_size_y = grid->getGridSizeY();

    char **chars = grid->getGrid();

    for (int i = 0; i < grid_size_y; i++)
    {
        chars[i] = new char[grid_size_x + 1];
        for (int j = 0; j < grid_size_x; j++)
        {
            if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1)
            {
                // Wall
                chars[i][j] = 'W';
            }
            else if (i == snake->getHeadY() && j == snake->getHeadX())
            {
                // Snake
                chars[i][j] = 'H';
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
                            if (newSpecialY != i && newSpecialX != j)
                            {
                                chars[newSpecialY][newSpecialX] = 'S';
                            }
                        }
                        generateNewFood(newX, newY);
                        if (newY != i && newX != j)
                        {
                            chars[newY][newX] = 'F';
                        }
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
                chars[i][j] = 'B';
            }
            else if (returnFoodOnThisField(i, j) == 0)
            {
                // Food
                chars[i][j] = 'F';
            }
            else if (returnFoodOnThisField(i, j) != -1)
            {
                // Food
                chars[i][j] = 'S';
            }
            else
            {
                // Grid floor
                chars[i][j] = 'x';
            }
        }
        chars[i][grid_size_x] = '\0';
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
    grid->setGrid(new char *[grid->getGridSizeY()]);
    snake = new Snake();
    updateGrid();
    game_over = false;
}