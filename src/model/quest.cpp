#include "quest.h"
#include "../services/gameControllerService.h"

bool Quest::checkWinCondition(WinCondition condition)
{
    std::shared_ptr<GameController> controller = GameControllerService::get();
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
Quest::Quest(std::string name, WinCondition *winCon)
{
    this->name = name;
    winCondition = winCon;
}

Quest::~Quest() {}