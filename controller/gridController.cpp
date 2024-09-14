#include "gridController.h"

GridController::GridController(){
    food = new Food[1];
}

GridController::~GridController(){

}

char **GridController::updateGrid(Grid *grid){
    // If a wall or the snake's body is reached, game over
    int grid_size_x = grid->getGridSizeX();
    int grid_size_y = grid->getGridSizeY();

    char **chars = grid->getGrid();

    for (int i = 0; i<grid_size_y; i++){
        chars[i] = new char[grid_size_x+1];
        for (int j = 0; j<grid_size_x; j++){
            if(i==0 || i==grid_size_y-1 || j==0 || j==grid_size_x-1){
                // Wall
                chars[i][j] = 'W';
            }else if(i == snake.getHeadY() && j == snake.getHeadX()){
                // Snake
                chars[i][j] = 'H';
                if(food[0].getPosX() == j && food[0].getPosY() == i){
                    snake.eat();
                    food[0].setPosX(9);
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
    int i = snake.getHeadY();
    int j = snake.getHeadX();
    if (i == 0 || i == grid->getGridSizeY() - 1 || j == 0 || j == grid->getGridSizeX() - 1)
    {
        game_over = true;
    }
    if(anyMovedBodypartOnThisField(i,j)){
        game_over = true;
    }
}

bool GridController::anyFoodOnThisField(int i, int j)
{
    return i == food[0].getPosY() && j == food[0].getPosX();
}

bool GridController::anyMovedBodypartOnThisField(int i, int j)
{
    for(int k = 0; k < snake.getBody()->size(); k++){
        if(snake.getBody()->at(k).getHasMoved() && i == snake.getBody()->at(k).getPosY() && j == snake.getBody()->at(k).getPosX()){
            return true;
        }
    }
    return false;
}

bool GridController::anyBodypartOnThisField(int i, int j)
{
    for(int k = 0; k < snake.getBody()->size(); k++){
        if(i == snake.getBody()->at(k).getPosY() && j == snake.getBody()->at(k).getPosX()){
            return true;
        }
    }
    return false;
}

void GridController::moveSnakeRight(){
    if(game_over){
        return;
    }
    int prevPos = snake.getHeadX();
    snake.setPosX(snake.getHeadX()+1);
    for(int i=0; i< snake.getBody()->size(); i++){
        int prevPosTemp = snake.getBody()->at(i).getPosX();
        if(snake.getBody()->at(i).getPosX() != prevPos && snake.getBody()->at(i).getPosX() != prevPos+1){
            snake.getBody()->at(i).setPosX(snake.getBody()->at(i).getPosX()+1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPos = prevPosTemp;
    }
}

void GridController::moveSnakeLeft(){
    if(game_over){
        return;
    }
    snake.setPosX(snake.getHeadX()-1);
    int prevPos = snake.getHeadX();
    for(int i=0; i< snake.getBody()->size(); i++){
        int prevPosTemp = snake.getBody()->at(i).getPosX();
        if(snake.getBody()->at(i).getPosX() != prevPos && snake.getBody()->at(i).getPosX() != prevPos-1){
            snake.getBody()->at(i).setPosX(snake.getBody()->at(i).getPosX()-1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPos = prevPosTemp;
    }
}

void GridController::moveSnakeUp(){
    if(game_over){
        return;
    }
    snake.setPosY(snake.getHeadY()+1);
    int prevPos = snake.getHeadY();
    for(int i=0; i< snake.getBody()->size(); i++){
        int prevPosTemp = snake.getBody()->at(i).getPosX();
        if(snake.getBody()->at(i).getPosY() != prevPos && snake.getBody()->at(i).getPosY() != prevPos+1){
            snake.getBody()->at(i).setPosY(snake.getBody()->at(i).getPosY()+1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPos = prevPosTemp;
    }
}

void GridController::moveSnakeDown(){
    if(game_over){
        return;
    }
    snake.setPosY(snake.getHeadY()-1);
    int prevPos = snake.getHeadY();
    for(int i=0; i< snake.getBody()->size(); i++){
        int prevPosTemp = snake.getBody()->at(i).getPosX();
        if(snake.getBody()->at(i).getPosY() != prevPos && snake.getBody()->at(i).getPosY() != prevPos-1){
            snake.getBody()->at(i).setPosY(snake.getBody()->at(i).getPosY()-1);
            snake.getBody()->at(i).setHasMoved(true);
        }
        prevPos = prevPosTemp;
    }
}

Snake *GridController::getSnake(){
    return &snake;
}

bool GridController::isGameOver(){
    return game_over;
}