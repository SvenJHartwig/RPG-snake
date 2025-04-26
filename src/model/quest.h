#pragma once
#include "winCondition.h"
#include "../controller/iGameController.h"
#include <string>

class Quest
{
public:
    bool checkWinCondition();
    std::string getName();
    Quest(std::string name, WinCondition *winCon);
    ~Quest();

private:
    std::string name;
    IGameController *controller;
    WinCondition *winCondition;
    bool checkWinCondition(WinCondition condition);
};