#pragma once

#include "gridController.h"
#include "../view/iGameView.h"

enum SpeedSetting
{
    l1 = 1000000,
    l2 = 8000000,
    l3 = 6000000,
    l4 = 4000000,
    l5 = 2000000,
    l6 = 1000000,
};

class GameController : public IGameController
{
private:
    Grid grid;
    GridController gridController;
    IGameView *view;
    bool windowClosed = false;
    char lastInput;
    SpeedSetting speed = l1;

public:
    void reactOnInput(char input);
    void setWindowClosed(bool closed);
    void setView(IGameView *view);
    void mainLoop();
    Grid getGrid();
};