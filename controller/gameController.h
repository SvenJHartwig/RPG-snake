#pragma once

#include "gridController.h"
#include "../view/iGameView.h"

class GameController : public IGameController
{
private:
    Grid grid;
    GridController gridController;
    IGameView *view;
    void reactOnInput(char input);
    bool windowClosed = false;

public:
    void setWindowClosed(bool closed);
    void setView(IGameView *view);
    void mainLoop();
    Grid getGrid();
};