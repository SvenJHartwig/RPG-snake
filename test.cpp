#include <catch2/catch.hpp>
#include "controller/gridController.h"
#include <string.h>
#include <iostream>
#include "controller/gameController.h"
#include "controller/iEatListener.h"

class TestGenerator : public RandomGenerator
{
  bool first;

public:
  int getRandom(int max_value) override
  {
    if (!first)
    {
      first = !first;
      return 9;
    }
    return 5;
  }
};

class TestEatListener : public IEatListener
{
public:
  void eat(bool isSpecial) {}
};

void printGridComparison(char **chars, char **expectedGrid, int gridSize)
{
  for (int i = 0; i < gridSize; i++)
  {
    std::cout << chars[i] << std::endl;
  }
  for (int i = 0; i < gridSize; i++)
  {
    std::cout << expectedGrid[i] << std::endl;
  }
}

TEST_CASE("Test grid movement")
{
  Grid grid;
  GridController *gridController = new GridController(new TestEatListener());
  gridController->setRNG(new TestGenerator());
  char **chars = grid.getGrid();
  int grid_size_x = grid.getGridSizeX();
  int grid_size_y = grid.getGridSizeY();
  char **expectedGrid = new char *[grid_size_x];
  Snake *snake = gridController->getSnake();
  Food *food = new Food[1];

  for (int i = 0; i < grid_size_y; i++)
  {
    expectedGrid[i] = new char[grid_size_x + 1];
    for (int j = 0; j < grid_size_x; j++)
    {
      if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1)
      {
        // Wall
        expectedGrid[i][j] = 'W';
      }
      else if (i == snake->getHeadY() && j == snake->getHeadX())
      {
        // Snake
        expectedGrid[i][j] = 'H';
      }
      else if (i == food[0].getPosY() && j == food[0].getPosX())
      {
        // Food
        expectedGrid[i][j] = 'F';
      }
      else
      {
        // Grid floor
        expectedGrid[i][j] = 'x';
      }
    }
    expectedGrid[i][grid_size_x] = '\0';
  }

  chars = gridController->updateGrid();
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(strcmp(chars[i], expectedGrid[i]) == 0);
  }
  gridController->moveSnakeRight();
  expectedGrid[snake->getHeadY()][snake->getHeadX() - 1] = 'x';
  expectedGrid[snake->getHeadY()][snake->getHeadX()] = 'H';
  chars = gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(strcmp(chars[i], expectedGrid[i]) == 0);
  }

  // Snake on Food
  gridController->moveSnakeRight();
  expectedGrid[snake->getHeadY()][snake->getHeadX() - 1] = 'x';
  expectedGrid[snake->getHeadY()][snake->getHeadX()] = 'H';
  expectedGrid[snake->getHeadY()][9] = 'F';
  chars = gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(strcmp(chars[i], expectedGrid[i]) == 0);
  }
  gridController->moveSnakeRight();
  expectedGrid[snake->getHeadY()][snake->getHeadX() - 1] = 'B';
  expectedGrid[snake->getHeadY()][snake->getHeadX()] = 'H';
  chars = gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(strcmp(chars[i], expectedGrid[i]) == 0);
  }
}

TEST_CASE("Test snake")
{
  GridController *gridController = new GridController(new TestEatListener());
  Snake *snake = gridController->getSnake();
  REQUIRE(snake->getBody()->size() == 0);
  int headX = snake->getHeadX();
  int headY = snake->getHeadY();
  // Snake eat generates a body at position of the head
  snake->eat();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  // If head moves right once, body stays where it is
  gridController->moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  // If head moves right again, body follows the head
  gridController->moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  // If head moves up, body follows the head
  gridController->moveSnakeUp();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  gridController->moveSnakeUp();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == --headY);
  // Second body part works
  snake->eat();
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY - 1);
  gridController->moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 2);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == --headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY + 1);
  gridController->moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 2);
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX - 1);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY);
  // Moving up the head first moves the body right
  gridController->moveSnakeUp();
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX - 1);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY);
}

TEST_CASE("Movement in opposite direction of last direction is not possible if snake is longer than 1")
{
  GameController *gameController = new GameController();
  gameController->eat(false);
  gameController->reactOnInput('a');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'a');
  gameController->reactOnInput('d');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'a');
  gameController->reactOnInput('w');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'w');
  gameController->reactOnInput('s');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'w');
  gameController->reactOnInput('d');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'd');
  gameController->reactOnInput('a');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'd');
  gameController->reactOnInput('s');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
  gameController->reactOnInput('w');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
}

TEST_CASE("Movement in opposite direction of last direction is possible if snake is exactly 1 long")
{
  GameController *gameController = new GameController();
  gameController->reactOnInput('a');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'a');
  gameController->reactOnInput('d');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'd');
  gameController->reactOnInput('w');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'w');
  gameController->reactOnInput('s');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
  gameController->reactOnInput('d');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'd');
  gameController->reactOnInput('a');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'a');
  gameController->reactOnInput('s');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
  gameController->reactOnInput('w');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 'w');
}

TEST_CASE("Test game over")
{
}

TEST_CASE("Speed setting increases")
{
  GameController *gameController = new GameController();
  GridController *gridController = gameController->getGridController();
  Snake *snake = gridController->getSnake();
  REQUIRE(gameController->getSpeed() == l1);
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l2);
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l3);
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l4);
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l5);
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l6);
}

TEST_CASE("sometimes one additional food is generated")
{
}