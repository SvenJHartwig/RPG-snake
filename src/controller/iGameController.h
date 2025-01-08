#pragma once

#include "../model/grid.h"
#include "../view/engine/iEngineCallback.h"

enum SpeedSetting
{
    l1 = 800000,
    l2 = 700000,
    l3 = 600000,
    l4 = 450000,
    l5 = 300000,
    l6 = 200000,
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