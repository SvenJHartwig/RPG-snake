#pragma once
#include "winCondition.h"
#include "../controller/iGameController.h"
#include <string>

class Quest
{
private:
    std::string name;
    IGameController *controller;
    WinCondition *winCondition;
    bool checkWinCondition(WinCondition condition);

public:
    bool checkWinCondition();
    std::string getName();
    Quest(std::string name, IGameController *controller, WinCondition *winCon);
    ~Quest();
};