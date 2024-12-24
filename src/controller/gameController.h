#pragma once

#include "gridController.h"
#include "../view/iGameView.h"
#include "../model/gameMode.h"
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
    long steps = 0;
    char lastDirection;
    GameState gameState = MAIN_MENU;
    bool infinite = true;
    int level = 1;
    IGameMode *gameMode;
    bool checkWinCondition();

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
    void softReset();
    void resetGame();
    int getLevel() { return level; }
    void setGameMode(GameModeEnum mode) { gameMode = GameModeFactory::createGameMode(mode); }
    IGameMode *getGameMode() { return gameMode; }
};