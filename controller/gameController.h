#pragma once

#include "gridController.h"
#include "../view/iGameView.h"

class GameController : public IGameController
{
private:
    Grid grid;
    GridController gridController;
    IGameView *view;
    bool windowClosed = false;
    char lastInput;

public:
    void reactOnInput(char input);
    void setWindowClosed(bool closed);
    void setView(IGameView *view);
    void mainLoop();
    Grid getGrid();
};