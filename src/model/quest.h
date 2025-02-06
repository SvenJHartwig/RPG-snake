#pragma once
#include "winCondition.h"
#include "../controller/iGameController.h"

class Quest
{
private:
    IGameController *controller;
    WinCondition *winCondition;
    bool checkWinCondition(WinCondition condition);

public:
    bool checkWinCondition();
    Quest(IGameController *controller, WinCondition *winCon);
    ~Quest();
};