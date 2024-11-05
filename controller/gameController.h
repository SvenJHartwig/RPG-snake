#pragma once

#include "gridController.h"
#include "../view/iGameView.h"
#include "iEatListener.h"

class GameController : public IGameController,
                       public IEatListener
{
private:
    GridController *gridController;
    IGameView *view;
    bool windowClosed = false;
    char lastInput;
    SpeedSetting speed = l1;
    int eatCount = 0;
    int score = 0;
    char lastDirection;
    GameState gameState = MAIN_MENU;

public:
    GameController();
    ~GameController();
    void reactOnInput(char input);
    void setWindowClosed(bool closed);
    void setView(IGameView *view);
    void mainLoop();
    void mainLoopIteration();
    Grid getGrid();
    GridController *getGridController();
    SpeedSetting getSpeed();
    void eat(bool isSpecial);
    char getLastDirection();
    char getLastInput() { return lastInput; }
    int getScore();
    GameState getGameState();
    void setGameState(GameState state) { this->gameState = state; }
    void resetGame();
};