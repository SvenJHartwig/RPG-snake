#pragma once

#include "../controller/iGameController.h"
#include "engine/elements/scene.h"
#include "engine/elements/spriteGrid.h"
#include "../model/winCondition.h"
#include "../model/quest.h"

class IGameView
{
public:
    virtual void setGameController(IGameController *gc) = 0;
    virtual int init() = 0;
    virtual void gameStateChanged(GameState game_state) = 0;
    virtual void setScore(int count) = 0;
    virtual void setHealth(int count) = 0;
    virtual void setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid) = 0;
    virtual ~IGameView() {};
    virtual void setQuests(std::vector<Quest *> *quests) = 0;
    virtual void showDialog(std::string text) = 0;
    virtual void closeDialog() = 0;
};