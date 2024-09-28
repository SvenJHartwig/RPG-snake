#include "gridController.h"
#include <cstdlib>
#include <time.h>

int RandomGeneratorImpl::getRandom(int max_value)
{
    return (rand() % max_value) + 1;
}

GridController::GridController()
{
    srand(time(NULL));
    rng = new RandomGeneratorImpl();
    food = new Food[1];
}

GridController::~GridController()
{
}

char **GridController::updateGrid(Grid *grid)
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
            else if (i == snake.getHeadY() && j == snake.getHeadX())
            {
                // Snake
                chars[i][j] = 'H';
                if (food[0].getPosX() == j && food[0].getPosY() == i)
                {
                    snake.eat();
                    int newX = rng->getRandom(grid->getGridSizeX() - 2);
                    int newY = rng->getRandom(grid->getGridSizeY() - 2);
                    food[0].setPosX(newX);
                    food[0].setPosY(newY);
                    if (newY != i && newX != j)
                    {
                        chars[newY][newX] = 'F';
                    }
                }
            }
            else if (anyBodypartOnThisField(i, j))
            {
                // Snake Body
                chars[i][j] = 'B';
            }
            else if (anyFoodOnThisField(i, j))
            {
                // Food
                chars[i][j] = 'F';
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
    int i = snake.getHeadY();
    int j = snake.getHeadX();
    if (i == 0 || i == grid->getGridSizeY() - 1 || j == 0 || j == grid->getGridSizeX() - 1)
    {
        game_over = true;
    }
    if (anyMovedBodypartOnThisField(i, j))
    {
        game_over = true;
    }
}

bool GridController::anyFoodOnThisField(int i, int j)
{
    return i == food[0].getPosY() && j == food[0].getPosX();
}

bool GridController::anyMovedBodypartOnThisField(int i, int j)
{
    for (int k = 0; k < snake.getBody()->size(); k++)
    {
        if (snake.getBody()->at(k).getHasMoved() && i == snake.getBody()->at(k).getPosY() && j == snake.getBody()->at(k).getPosX())
        {
            return true;
        }
    }
    return false;
}

bool GridController::anyBodypartOnThisField(int i, int j)
{
    for (int k = 0; k < snake.getBody()->size(); k++)
    {
        if (i == snake.getBody()->at(k).getPosY() && j == snake.getBody()->at(k).getPosX())
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
    snake.setPosX(snake.getHeadX() + 1);
    int prevPosX = snake.getHeadX();
    int prevPosY = snake.getHeadY();
    for (int i = 0; i < snake.getBody()->size(); i++)
    {
        int prevPosTempX = snake.getBody()->at(i).getPosX();
        int prevPosTempY = snake.getBody()->at(i).getPosY();
        if (snake.getBody()->at(i).getPosY() == prevPosY - 1 || snake.getBody()->at(i).getPosY() == prevPosY + 1)
        {
            snake.getBody()->at(i).setPosY(prevPosY);
            snake.getBody()->at(i).setHasMoved(true);
        }
        else if (snake.getBody()->at(i).getPosX() != prevPosX - 1 && snake.getBody()->at(i).getPosX() != prevPosX)
        {
            snake.getBody()->at(i).setPosX(snake.getBody()->at(i).getPosX() + 1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPosX = prevPosTempX;
        prevPosY = prevPosTempY;
    }
}

void GridController::moveSnakeLeft()
{
    if (game_over)
    {
        return;
    }
    snake.setPosX(snake.getHeadX() - 1);
    int prevPosX = snake.getHeadX();
    int prevPosY = snake.getHeadY();
    for (int i = 0; i < snake.getBody()->size(); i++)
    {
        int prevPosTempX = snake.getBody()->at(i).getPosX();
        int prevPosTempY = snake.getBody()->at(i).getPosY();
        if (snake.getBody()->at(i).getPosY() == prevPosY - 1 || snake.getBody()->at(i).getPosY() == prevPosY + 1)
        {
            snake.getBody()->at(i).setPosY(prevPosY);
            snake.getBody()->at(i).setHasMoved(true);
        }
        else if (snake.getBody()->at(i).getPosX() != prevPosX + 1 && snake.getBody()->at(i).getPosX() != prevPosX)
        {
            snake.getBody()->at(i).setPosX(snake.getBody()->at(i).getPosX() - 1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPosX = prevPosTempX;
        prevPosY = prevPosTempY;
    }
}

void GridController::moveSnakeUp()
{
    if (game_over)
    {
        return;
    }
    snake.setPosY(snake.getHeadY() - 1);
    int prevPosX = snake.getHeadX();
    int prevPosY = snake.getHeadY();
    for (int i = 0; i < snake.getBody()->size(); i++)
    {
        int prevPosTempX = snake.getBody()->at(i).getPosX();
        int prevPosTempY = snake.getBody()->at(i).getPosY();
        if (snake.getBody()->at(i).getPosX() == prevPosX - 1 || snake.getBody()->at(i).getPosX() == prevPosX + 1)
        {
            snake.getBody()->at(i).setPosX(prevPosX);
            snake.getBody()->at(i).setHasMoved(true);
        }
        else if (snake.getBody()->at(i).getPosY() != prevPosY + 1 && snake.getBody()->at(i).getPosY() != prevPosY)
        {
            snake.getBody()->at(i).setPosY(snake.getBody()->at(i).getPosY() - 1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPosX = prevPosTempX;
        prevPosY = prevPosTempY;
    }
}

void GridController::moveSnakeDown()
{
    if (game_over)
    {
        return;
    }
    snake.setPosY(snake.getHeadY() + 1);
    int prevPosX = snake.getHeadX();
    int prevPosY = snake.getHeadY();
    for (int i = 0; i < snake.getBody()->size(); i++)
    {
        int prevPosTempX = snake.getBody()->at(i).getPosX();
        int prevPosTempY = snake.getBody()->at(i).getPosY();
        if (snake.getBody()->at(i).getPosX() == prevPosX - 1 || snake.getBody()->at(i).getPosX() == prevPosX + 1)
        {
            snake.getBody()->at(i).setPosX(prevPosX);
            snake.getBody()->at(i).setHasMoved(true);
        }
        else if (snake.getBody()->at(i).getPosY() != prevPosY - 1 && snake.getBody()->at(i).getPosY() != prevPosY)
        {
            snake.getBody()->at(i).setPosY(snake.getBody()->at(i).getPosY() + 1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPosX = prevPosTempX;
        prevPosY = prevPosTempY;
    }
}

Snake *GridController::getSnake()
{
    return &snake;
}

bool GridController::isGameOver()
{
    return game_over;
}

void GridController::setRNG(RandomGenerator *rng)
{
    this->rng = rng;
}