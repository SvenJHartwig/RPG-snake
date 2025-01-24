#pragma once

#include "gridController.h"
#include "../view/iGameView.h"
#include "../model/gameMode.h"
#include "iEatListener.h"
#include "iSoundController.h"

class GameController : public IGameController,
                       public IEatListener
{
private:
    GridController *gridController;
    IGameView *view;
    ISoundController *soundController;
    bool windowClosed = false;
    char lastInput;
    SpeedSetting speed = l1;
    int eatCount = 0;
    int score = 0;
    int ticksSinceMovement = 0;
    long steps = 0;
    char lastDirection = ' ';
    GameState gameState = MAIN_MENU;
    int level = 1;
    IGameMode *gameMode;

public:
    GameController();
    ~GameController();
    void reactOnInput(int input) override;
    void setWindowClosed(bool closed) override;
    void setView(IGameView *view);
    void setSoundController(ISoundController *soundController);
    void mainLoop();
    void mainLoopIteration();
    GridController *getGridController();
    SpeedSetting getSpeed();
    void eat(bool isSpecial) override;
    char getLastDirection();
    char getLastInput() { return lastInput; }
    int getScore() override;
    long getSteps() override { return steps; }
    GameState getGameState() override;
    void setGameState(GameState state) { this->gameState = state; }
    void softReset();
    void resetGame();
    int getLevel() { return level; }
    void setTicksSinceLastMovement(int ticksSinceMovement) { this->ticksSinceMovement = ticksSinceMovement; }
    void setGameMode(GameModeEnum mode) { gameMode = GameModeFactory::createGameMode(mode, this); }
    IGameMode *getGameMode() { return gameMode; }
};