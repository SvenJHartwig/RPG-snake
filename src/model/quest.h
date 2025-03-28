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
    bool checkWinCondition(WinCondition condition, IGameController *controller);

public:
    bool checkWinCondition(IGameController *controller);
    std::string getName();
    Quest(std::string name, WinCondition *winCon);
    ~Quest();
};