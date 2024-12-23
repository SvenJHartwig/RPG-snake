#include "testClasses.h"
#include "../src/view/engine/elements/scene.h"

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
  vector<string> *chars = grid.getLevel();
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
      else
      {
        // Grid floor
        expectedGrid->at(i)[j] = 'x';
      }
    }
  }

  gridController->updateGrid();
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  gridController->moveSnakeRight();
  gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  REQUIRE(gridController->getSnake()->getPosX() == 6);
  REQUIRE(gridController->getSnake()->getPosY() == 5);
  REQUIRE(gridController->getFood()->at(0)->getPosX() == 7);

  // Snake on Food
  gridController->moveSnakeRight();
  gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  REQUIRE(gridController->getSnake()->getPosX() == 7);
  REQUIRE(gridController->getSnake()->getPosY() == 5);
  REQUIRE(gridController->getFood()->at(0)->getPosX() == 9);
  REQUIRE(gridController->getFood()->at(0)->getPosY() == 5);

  gridController->moveSnakeRight();
  gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  REQUIRE(gridController->getSnake()->getPosX() == 8);
  REQUIRE(gridController->getSnake()->getPosY() == 5);
  REQUIRE(gridController->getFood()->at(0)->getPosX() == 9);
  REQUIRE(gridController->getFood()->at(0)->getPosY() == 5);

  // Eating special food does not increase snake length
  gridController->generateNewSpecialFood(snake->getPosX() + 2, snake->getPosY());
  gridController->moveSnakeRight();
  gridController->moveSnakeRight();
  gridController->updateGrid();
  REQUIRE(!gridController->isGameOver());
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  REQUIRE(snake->getBody()->size() == 1);
}

TEST_CASE("Test snake")
{
  GridController *gridController = new GridController(new TestEatListener());
  Snake *snake = gridController->getSnake();
  REQUIRE(snake->getBody()->size() == 0);
  int headX = snake->getPosX();
  int headY = snake->getPosY();
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
  // Set gamestate to INGAME
  gameController->setView(new TestView());
  gameController->reactOnInput('p');
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
  gameController->reactOnInput('e');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
  gameController->reactOnInput('l');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
  gameController->reactOnInput('p');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
  gameController->setGameState(EXIT);
  gameController->reactOnInput('i');
  gameController->mainLoopIteration();
  REQUIRE(gameController->getLastDirection() == 's');
}

TEST_CASE("Movement in opposite direction of last direction is possible if snake is exactly 1 long")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
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
  gameController->setView(new TestView());
  GridController *gridController = gameController->getGridController();
  gridController->setRNG(new TestGenerator());
  Snake *snake = gridController->getSnake();
  REQUIRE(gameController->getSpeed() == l1);
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l2);
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l3);
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l4);
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l5);
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  REQUIRE(gameController->getSpeed() == l6);
}

TEST_CASE("sometimes one additional food is generated")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  GridController *gridController = gameController->getGridController();
  TestGenerator *trng = new TestGenerator();
  gridController->setRNG(trng);
  Snake *snake = gridController->getSnake();
  REQUIRE(gridController->getFood()->size() == 1);
  trng->specificValue = 2;
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
  gridController->updateGrid();
  REQUIRE(gridController->getFood()->size() == 1);
  trng->specificValue = 1;
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
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
  int oldHeadX = gameController->getGridController()->getSnake()->getPosX();
  int oldHeadY = gameController->getGridController()->getSnake()->getPosY();
  gameController->getGridController()->moveSnakeDown();
  REQUIRE(gameController->getGridController()->getSnake()->getPosY() == oldHeadY);
  gameController->getGridController()->moveSnakeUp();
  REQUIRE(gameController->getGridController()->getSnake()->getPosY() == oldHeadY);
  gameController->getGridController()->moveSnakeRight();
  REQUIRE(gameController->getGridController()->getSnake()->getPosX() == oldHeadX);
  gameController->getGridController()->moveSnakeLeft();
  REQUIRE(gameController->getGridController()->getSnake()->getPosX() == oldHeadX);
  gameController->reactOnInput('p');
  REQUIRE(gameController->getGameState() == MAIN_MENU);
}

TEST_CASE("Special food has a time out")
{
  SpecialFood *spFood = new SpecialFood();
  REQUIRE(spFood->remainingTime() == 20);
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  GridController *gridController = gameController->getGridController();
  TestGenerator *trng = new TestGenerator();
  gridController->setRNG(trng);
  Snake *snake = gridController->getSnake();
  trng->specificValue = 1;
  gridController->generateNewFood(snake->getPosX(), snake->getPosY());
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
  GridController *gridController = new GridController(new TestEatListener());
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
      else
      {
        // Grid floor
        expectedGrid->at(i)[j] = 'x';
      }
    }
  }
  string path = RESOURCE_DIR;
  gridController->loadLevel(path.c_str());
  path.append("/tests/level/level1");
  gridController->loadLevel(path.c_str());
  vector<string> *chars = grid->getLevel();
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars->at(i).compare(expectedGrid->at(i)) == 0);
  }
  gridController->updateGrid();
  vector<string> *chars2 = grid->getLevel();
  for (int i = 0; i < grid_size_y; i++)
  {
    REQUIRE(chars2->at(i).compare(expectedGrid->at(i)) == 0);
  }
  REQUIRE(gridController->getSnake()->getPosX() == 5);
  REQUIRE(gridController->getSnake()->getPosY() == 5);
  REQUIRE(gridController->getFood()->size() == 1);
  REQUIRE(gridController->getFood()->at(0)->getPosX() == 7);
  REQUIRE(gridController->getFood()->at(0)->getPosY() == 5);
}

TEST_CASE("If snake goes out of bounds, wrap around")
{
  GridController *gridController = new GridController(new TestEatListener());
  Grid *grid = gridController->getGrid();
  int grid_size_x = grid->getGridSizeX();
  int grid_size_y = grid->getGridSizeY();
  string path = RESOURCE_DIR;
  path.append("/tests/level/level2");
  gridController->loadLevel(path.c_str());
  vector<string> *chars = grid->getLevel();
  gridController->moveSnakeUp();
  gridController->moveSnakeUp();
  gridController->moveSnakeUp();
  gridController->moveSnakeUp();
  gridController->moveSnakeUp();
  gridController->moveSnakeUp();
  gridController->updateGrid();
  REQUIRE(gridController->getGrid()->getGridSizeY() == 20);
  REQUIRE(gridController->getSnake()->getPosY() == grid_size_y - 1);
}

TEST_CASE("Only appropriate input works while in game")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  gameController->reactOnInput('o');
  REQUIRE(gameController->getGameState() == IN_GAME);
  gameController->reactOnInput('a');
  gameController->reactOnInput('p');
  REQUIRE(gameController->getLastInput() == 'a');
}

TEST_CASE("Exit game")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  gameController->reactOnInput('l');
  REQUIRE(gameController->getGameState() == EXIT);
}

TEST_CASE("Win game")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  gameController->reactOnInput('o');
  REQUIRE(gameController->getLevel() == 1);
  REQUIRE(gameController->getGameState() == IN_GAME);
  // Eat 20 special foods for 40 points
  for (int i = 0; i < 20; i++)
  {
    gameController->eat(true);
  }
  gameController->mainLoopIteration();
  REQUIRE(gameController->getGameState() == WIN);
  gameController->reactOnInput('p');
  REQUIRE(gameController->getGameState() == IN_GAME);
  REQUIRE(gameController->getLevel() == 2);
  // Hard reset on restarting game
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
  gameController->reactOnInput('p');
  REQUIRE(gameController->getGameState() == IN_GAME);
  REQUIRE(gameController->getLevel() == 1);
  REQUIRE(gameController->getScore() == 0);
}

TEST_CASE("Infinite game")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  gameController->reactOnInput('p');
  REQUIRE(gameController->getGameState() == IN_GAME);
  for (int i = 0; i < 20; i++)
  {
    gameController->eat(true);
  }
  REQUIRE(gameController->getGameState() == IN_GAME);
}

TEST_CASE("RNG doesn't generate pair on wall")
{
  RandomGeneratorImpl *rng = new RandomGeneratorImpl();
  for (int i = 0; i < 40; i++)
  {
    std::pair<int, int> pair = rng->getRandomPair(2, 1, {{0, 1}});
    std::pair<int, int> pair2 = {0, 1};
    REQUIRE(pair != pair2);
  }
}

TEST_CASE("Load level with win condition from disk")
{
  GridController *gridController = new GridController(new TestEatListener());
  string path = RESOURCE_DIR;
  path.append("/tests/level/levelWithWincon");
  gridController->loadLevel(path.c_str());
  REQUIRE(WinCondition(SCORE, 40) == *(gridController->getWinCondition()));
  path.append("2");
  gridController->loadLevel(path.c_str());
  REQUIRE(WinCondition(TIME, 20) == *(gridController->getWinCondition()));
}

TEST_CASE("Win game with win condition: time")
{
  GameController *gameController = new GameController();
  gameController->setView(new TestView());
  gameController->reactOnInput('o');
  string path = RESOURCE_DIR;
  path.append("/tests/level/levelWithWincon2");
  gameController->getGridController()->loadLevel(path.c_str());
  REQUIRE(gameController->getGameState() == IN_GAME);
  // 10 Steps to the right
  gameController->reactOnInput('d');
  for (int i = 0; i < 10; i++)
  {
    gameController->mainLoopIteration();
  }
  // 10 Steps to the bottom
  gameController->reactOnInput('s');
  for (int i = 0; i < 10; i++)
  {
    gameController->mainLoopIteration();
  }
  // After 20 steps, the win condition is fulfilled
  REQUIRE(gameController->getGameState() == WIN);
}