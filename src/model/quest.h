#pragma once
#include "winCondition.h"
#include "../controller/iGameController.h"
#include <string>

class Quest
{
public:
    bool checkWinCondition();
    std::string getName();
    bool getIsFinished();
    Quest(std::string name, WinCondition *winCon);
    ~Quest();

private:
    std::string name;
    bool isFinished;
    IGameController *controller;
    WinCondition *winCondition;
};