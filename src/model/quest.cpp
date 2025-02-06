#include "quest.h"

bool Quest::checkWinCondition(WinCondition condition)
{
    if (condition.getType() == SCORE)
    {
        if (controller->getScore() >= condition.getAmount())
        {
            return true;
        }
    }
    if (condition.getType() == TIME)
    {
        if (controller->getSteps() >= condition.getAmount())
        {
            return true;
        }
    }
    return false;
}
bool Quest::checkWinCondition()
{
    return checkWinCondition(*winCondition);
}

std::string Quest::getName()
{
    return name;
}
Quest::Quest(std::string name, IGameController *controller, WinCondition *winCon)
{
    this->name = name;
    this->controller = controller;
    winCondition = winCon;
}

Quest::~Quest() {}