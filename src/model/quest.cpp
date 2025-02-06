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
Quest::Quest(IGameController *controller, WinCondition *winCon)
{
    this->controller = controller;
    winCondition = winCon;
}

Quest::~Quest() {}