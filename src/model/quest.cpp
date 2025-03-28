#include "quest.h"

bool Quest::checkWinCondition(WinCondition condition, IGameController *controller)
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
bool Quest::checkWinCondition(IGameController *controller)
{
    return checkWinCondition(*winCondition, controller);
}

std::string Quest::getName()
{
    return name;
}
Quest::Quest(std::string name, WinCondition *winCon)
{
    this->name = name;
    winCondition = winCon;
}

Quest::~Quest() {}