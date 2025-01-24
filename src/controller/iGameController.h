#pragma once

#include "../model/grid.h"
#include "../view/engine/iEngineCallback.h"

enum SpeedSetting
{
    l1 = 100,
    l2 = 80,
    l3 = 60,
    l4 = 40,
    l5 = 30,
    l6 = 20,
};

enum GameState
{
    MAIN_MENU,
    IN_GAME,
    GAME_OVER,
    EXIT,
    WIN,
};

class IGameController : public SEngine::IEngineCallback
{
public:
    virtual int getScore() = 0;
    virtual long getSteps() = 0;
    virtual GameState getGameState() = 0;
};