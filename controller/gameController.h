#pragma once

#include "gridController.h"
#include "../view/iGameView.h"
#include "iEatListener.h"

enum SpeedSetting
{
    l1 = 800000,
    l2 = 700000,
    l3 = 600000,
    l4 = 450000,
    l5 = 300000,
    l6 = 200000,
};

class GameController : public IGameController, public IEatListener
{
private:
    GridController *gridController;
    IGameView *view;
    bool windowClosed = false;
    char lastInput;
    SpeedSetting speed = l1;
    int eatCount = 0;
    char lastDirection;

public:
    GameController();
    ~GameController();
    void reactOnInput(char input);
    void setWindowClosed(bool closed);
    void setView(IGameView *view);
    void mainLoop();
    Grid getGrid();
    GridController *getGridController();
    SpeedSetting getSpeed();
    void eat();
    char getLastDirection();
};