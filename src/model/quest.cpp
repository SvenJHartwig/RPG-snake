#include "quest.h"
#include "../services/gameControllerService.h"

bool Quest::checkWinCondition()
{
    std::shared_ptr<GameController> controller = GameControllerService::get();
    if (winCondition->getType() == SCORE)
    {
        if (controller->getScore() >= winCondition->getAmount())
        {
            isFinished = true;
            return true;
        }
    }
    if (winCondition->getType() == TIME)
    {
        if (controller->getSteps() >= winCondition->getAmount())
        {
            isFinished = true;
            return true;
        }
    }
    return false;
}

std::string Quest::getName()
{
    return name;
}
bool Quest::getIsFinished()
{
    return isFinished;
}
Quest::Quest(std::string name, WinCondition *winCon)
{
    this->name = name;
    winCondition = winCon;
    isFinished = false;
}

Quest::~Quest() {}