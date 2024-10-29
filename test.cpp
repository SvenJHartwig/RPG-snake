#include <catch2/catch.hpp>
#include "controller/gridController.h"
#include <string.h>
#include <iostream>
#include "controller/gameController.h"
#include "controller/iEatListener.h"
#include "view/elements/scene.h"

class TestGenerator : public RandomGenerator
{
  bool first = false;

public:
  int specificValue = 0;
  int getRandom(int max_value) override
  {
    if (specificValue != 0)
    {
      return specificValue;
    }
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

class TestView : public IGameView
{
  void setGameController(IGameController *gc) {}
  void renderingLoop() {}
  int init() { return 0; }
  void showGrid(vector<string> *grid, int grid_size_x, int grid_size_y) {}
  void gameStateChanged(GameState game_state) {}
  void setCurrentScene(Scene *current_scene) {}
};

void printGridComparison(vector<string> *chars, vector<string> *expectedGrid, int gridSize)
{
  std::cout << "Actual: " << std::endl;
  for (const std::string &str : *chars)
  {
    std::cout << str << std::endl;
  }
  std::cout << "Expected: " << std::endl;
  for (const std::string &str : *expectedGrid)
  {
    std::cout << str << std::endl;
  }
}

TEST_CASE("Test grid movement")
{
  Grid grid;
  GridController *gridController = new GridController(new TestEatListener());
  gridController->setRNG(new TestGenerator());
  vector<string> *chars = grid.getGrid();
  int grid_size_x = grid.getGridSizeX();
  int grid_size_y = grid.getGridSizeY();
  vector<string> *expectedGrid = new vector<string>();
  Snake *snake = gridController->getSnake();
  Food *food = new Food[1];

  for (int i = 0; i < grid_size_y; i++)
  {
    string temp(grid_size_y, 'x');
    expectedGrid->push_back(temp);
    for (int j = 0; j < grid_size_x; j++)
    {
      if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1)
      {
        // Wall
        expectedGrid->at(i)[j] = 'W';
      }
      else if (i == snake->getHeadY() && j == snake->getHeadX())
      {
        // Snake
        expectedGrid->at(i)[j] = 'H';
      }
      else if (i == food[0].getPosY() && j == food[0].getPosX())
      {
        // Food
        expectedGrid->at(i)[j] = 'F';
      }
      else
      {
        // Grid floor
        expectedGrid->at(i)[j] = 'x';
      }
    }
  }

  chars = gridController->updateGrid();
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  gridController->moveSnakeRight();
  expectedGrid->at(snake->getHeadY())[snake->getHeadX() - 1] = 'x';
  expectedGrid->at(snake->getHeadY())[snake->getHeadX()] = 'H';
  chars = gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }

  // Snake on Food
  gridController->moveSnakeRight();
  expectedGrid->at(snake->getHeadY())[snake->getHeadX() - 1] = 'x';
  expectedGrid->at(snake->getHeadY())[snake->getHeadX()] = 'H';
  expectedGrid->at(snake->getHeadY())[9] = 'F';
  chars = gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  gridController->moveSnakeRight();
  expectedGrid->at(snake->getHeadY())[snake->getHeadX() - 1] = 'B';
  expectedGrid->at(snake->getHeadY())[snake->getHeadX()] = 'H';
  chars = gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
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

TEST_CASE("Speed setting increases")
{
  GameController *gameController = new GameController();
  GridController *gridController = gameController->getGridController();
  gridController->setRNG(new TestGenerator());
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
  GameController *gameController = new GameController();
  GridController *gridController = gameController->getGridController();
  TestGenerator *trng = new TestGenerator();
  gridController->setRNG(trng);
  Snake *snake = gridController->getSnake();
  REQUIRE(gridController->getFood()->size() == 1);
  trng->specificValue = 2;
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gridController->getFood()->size() == 1);
  trng->specificValue = 1;
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gridController->getFood()->size() == 2);
}

TEST_CASE("Pressing enter starts game")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  REQUIRE(gameController->getGameState() == MAIN_MENU);
  gameController->reactOnInput('p');
  REQUIRE(gameController->getGameState() == IN_GAME);
}

TEST_CASE("After Game Over pause before going to main menu")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  gameController->getGridController()->moveSnakeUp();
  gameController->getGridController()->moveSnakeUp();
  gameController->getGridController()->moveSnakeUp();
  gameController->getGridController()->moveSnakeUp();
  gameController->getGridController()->moveSnakeUp();
  gameController->getGridController()->updateGrid();
  gameController->mainLoopIteration();
  REQUIRE(gameController->getGridController()->isGameOver());
  REQUIRE(gameController->getGameState() == GAME_OVER);
  gameController->reactOnInput('p');
  REQUIRE(gameController->getGameState() == MAIN_MENU);
}

TEST_CASE("Special food has a time out")
{
  SpecialFood *spFood = new SpecialFood();
  REQUIRE(spFood->remainingTime() == 20);
  GameController *gameController = new GameController();
  GridController *gridController = gameController->getGridController();
  TestGenerator *trng = new TestGenerator();
  gridController->setRNG(trng);
  Snake *snake = gridController->getSnake();
  trng->specificValue = 1;
  gridController->generateNewFood(snake->getHeadX(), snake->getHeadY());
  gridController->updateGrid();
  REQUIRE(gridController->getFood()->size() == 2);
  spFood = (SpecialFood *)gridController->getFood()->at(1);
  for (int i = 20; i > 0; i--)
  {
    REQUIRE(spFood->remainingTime() == i);
    gridController->moveSnakeDown();
  }
  REQUIRE(gridController->getFood()->size() == 1);
}

TEST_CASE("Load level from disk")
{
  GameController *gameController = new GameController();
  GridController *gridController = gameController->getGridController();
  Grid *grid = gridController->getGrid();
  int grid_size_x = grid->getGridSizeX();
  int grid_size_y = grid->getGridSizeY();
  vector<string> *expectedGrid = new vector<string>();
  Snake *snake = gridController->getSnake();
  Food *food = new Food[1];

  for (int i = 0; i < grid_size_y; i++)
  {
    string temp(grid_size_y, 'x');
    expectedGrid->push_back(temp);
    for (int j = 0; j < grid_size_x; j++)
    {
      if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1 || i == 1 && j == 1)
      {
        // Wall
        expectedGrid->at(i)[j] = 'W';
      }
      else if (i == snake->getHeadY() && j == snake->getHeadX())
      {
        // Snake
        expectedGrid->at(i)[j] = 'H';
      }
      else if (i == food[0].getPosY() && j == food[0].getPosX())
      {
        // Food
        expectedGrid->at(i)[j] = 'F';
      }
      else
      {
        // Grid floor
        expectedGrid->at(i)[j] = 'x';
      }
    }
  }
  gridController->loadLevel("./resources/level/level1");
  vector<string> *chars = grid->getLevel();
  printGridComparison(chars, expectedGrid, grid_size_y);
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
}