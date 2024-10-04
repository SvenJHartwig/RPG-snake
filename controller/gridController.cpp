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
    food = new std::vector<Food>();
    food->push_back(*(new Food()));
    grid = new Grid();
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
            else if (i == snake.getHeadY() && j == snake.getHeadX())
            {
                // Snake
                chars[i][j] = 'H';
                if (anyFoodOnThisField())
                {
                    snake.eat();
                    eatListener->eat();
                    int newX = rng->getRandom(grid->getGridSizeX() - 2);
                    int newY = rng->getRandom(grid->getGridSizeY() - 2);
                    generateNewFood(newX, newY);
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
    return i == food->at(0).getPosY() && j == food->at(0).getPosX();
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
    moveSnakeBody();
    snake.setPosX(snake.getHeadX() + 1);
}

void GridController::moveSnakeLeft()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake.setPosX(snake.getHeadX() - 1);
}

void GridController::moveSnakeUp()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake.setPosY(snake.getHeadY() - 1);
}

void GridController::moveSnakeDown()
{
    if (game_over)
    {
        return;
    }
    moveSnakeBody();
    snake.setPosY(snake.getHeadY() + 1);
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

void GridController::moveSnakeBody()
{
    if (snake.getBody()->size() > 0)
    {
        SnakeBodyPart temp = snake.getBody()->at(snake.getBody()->size() - 1);
        temp.setHasMoved(true);
        temp.setPosX(snake.getHeadX());
        temp.setPosY(snake.getHeadY());
        snake.getBody()->pop_back();
        snake.getBody()->insert(snake.getBody()->begin(), temp);
    }
}

void GridController::generateNewFood(int i, int j)
{
    food->at(0).setPosX(i);
    food->at(0).setPosY(j);
}

Grid *GridController::getGrid()
{
    return grid;
}