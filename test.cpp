#include <catch2/catch.hpp>
#include "controller/gridController.h"
#include <string.h>
#include <iostream>

class TestGenerator : public RandomGenerator{
  bool first;
  public:
    int getRandom(int max_value) override{
      if(!first){
        first = !first;
        return 9;
      }
      return 5;
    }
};

void printGridComparison(char **chars, char **expectedGrid, int gridSize){
  for (int i = 0; i < gridSize; i++){
      std::cout << chars[i] << std::endl;
  }
  for (int i = 0; i < gridSize; i++){
      std::cout << expectedGrid[i] << std::endl;
  }
}

TEST_CASE( "Test grid movement" ) {
  Grid grid;
  GridController gridController;
  gridController.setRNG(new TestGenerator());
  char **chars = grid.getGrid();
  int grid_size_x = grid.getGridSizeX();
  int grid_size_y = grid.getGridSizeY();
  char **expectedGrid = new char*[grid_size_x];
  Snake *snake = gridController.getSnake();
  Food *food = new Food[1];

  for (int i = 0; i<grid_size_y; i++){
      expectedGrid[i] = new char[grid_size_x+1];
      for (int j = 0; j<grid_size_x; j++){
          if(i==0 || i==grid_size_y-1 || j==0 || j==grid_size_x-1){
              // Wall
              expectedGrid[i][j] = 'W';
          }else if(i == snake->getHeadY() && j == snake->getHeadX()){
              // Snake
              expectedGrid[i][j] = 'H';
          }else if(i == food[0].getPosY() && j == food[0].getPosX()){
              // Food
              expectedGrid[i][j] = 'F';
          } else {
              // Grid floor
              expectedGrid[i][j] = 'x';
          }
      }
      expectedGrid[i][grid_size_x] = '\0';
  }

  chars = gridController.updateGrid(&grid);
  for (int i = 0; i<grid_size_y; i++){
    REQUIRE( strcmp(chars[i], expectedGrid[i]) == 0 );
  }
  gridController.moveSnakeRight();
  expectedGrid[snake->getHeadY()][snake->getHeadX()-1] = 'x';
  expectedGrid[snake->getHeadY()][snake->getHeadX()] = 'H';
  chars = gridController.updateGrid(&grid);
  REQUIRE(!gridController.isGameOver());
  for (int i = 0; i<grid_size_y; i++){
    REQUIRE( strcmp(chars[i], expectedGrid[i]) == 0 );
  }

  // Snake on Food
  gridController.moveSnakeRight();
  expectedGrid[snake->getHeadY()][snake->getHeadX()-1] = 'x';
  expectedGrid[snake->getHeadY()][snake->getHeadX()] = 'H';
  expectedGrid[snake->getHeadY()][9] = 'F';
  chars = gridController.updateGrid(&grid);
  REQUIRE(!gridController.isGameOver());
  for (int i = 0; i<grid_size_y; i++){
    REQUIRE( strcmp(chars[i], expectedGrid[i]) == 0 );
  }
  gridController.moveSnakeRight();
  expectedGrid[snake->getHeadY()][snake->getHeadX()-1] = 'B';
  expectedGrid[snake->getHeadY()][snake->getHeadX()] = 'H';
  chars = gridController.updateGrid(&grid);
  REQUIRE(!gridController.isGameOver());
  for (int i = 0; i<grid_size_y; i++){
    REQUIRE( strcmp(chars[i], expectedGrid[i]) == 0 );
  }
}

TEST_CASE( "Test snake" ) {
  GridController gridController;
  Snake *snake = gridController.getSnake();
  REQUIRE(snake->getBody()->size() == 0);
  int headX = snake->getHeadX();
  int headY = snake->getHeadY();
  // Snake eat generates a body at position of the head
  snake->eat();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  // If head moves right once, body stays where it is
  gridController.moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  // If head moves right again, body follows the head
  gridController.moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  // If head moves up, body follows the head
  gridController.moveSnakeUp();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == ++headY);
  gridController.moveSnakeUp();
  REQUIRE(snake->getBody()->size() == 1);
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == ++headY);
  // Second body part works
  snake->eat();
  REQUIRE(snake->getBody()->at(0).getPosX() == headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX+1);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY);
  gridController.moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 2);
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY);
  gridController.moveSnakeRight();
  REQUIRE(snake->getBody()->size() == 2);
  REQUIRE(snake->getBody()->at(0).getPosX() == ++headX);
  REQUIRE(snake->getBody()->at(0).getPosY() == headY);
  REQUIRE(snake->getBody()->at(1).getPosX() == headX-1);
  REQUIRE(snake->getBody()->at(1).getPosY() == headY);
}
