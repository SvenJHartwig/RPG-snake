#pragma once

#include "../controller/iGameController.h"
#include "engine/elements/scene.h"

class IGameView
{
public:
    virtual void setGameController(IGameController *gc) = 0;
    virtual void renderingLoop() = 0;
    virtual int init() = 0;
    virtual void gameStateChanged(GameState game_state) = 0;
    virtual void setScore(int count) = 0;
    virtual void setGrid(std::vector<std::string> *grid) = 0;
    virtual ~IGameView() {};
};