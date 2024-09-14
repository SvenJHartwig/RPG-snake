#include "gameController.h"
#include <unistd.h>

void GameController::mainLoop(){
    while(!gridController.isGameOver()){
        char **chars = gridController.updateGrid(&grid);
        view.showGrid(chars, grid.getGridSizeY());
        usleep(1000000);
        gridController.moveSnakeRight();
    }
}