#include "gameMode.h"

IGameMode *GameModeFactory::createGameMode(GameModeEnum mode, IGameController *controller)
{
    switch (mode)
    {
    case INFINITE:
        return new InfiniteGameMode(controller);
    case RPG:
        return new RPGGameMode(controller);
    default:
        return new InfiniteGameMode(controller);
    }
}

InfiniteGameMode::InfiniteGameMode(IGameController *controller)
{
}

void InfiniteGameMode::clearQuests() {}
void InfiniteGameMode::addQuest(WinCondition condition) {}

bool InfiniteGameMode::checkWinCondition()
{
    return false;
}

bool InfiniteGameMode::operator==(IGameMode const &other) const
{
    if (dynamic_cast<const InfiniteGameMode *>(&other))
        return true;
    return false;
}
bool InfiniteGameMode::hasHealth()
{
    return false;
}

RPGGameMode::RPGGameMode(IGameController *controller)
{
    this->controller = controller;
}

bool RPGGameMode::checkWinCondition(WinCondition condition)
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

void RPGGameMode::clearQuests()
{
    quests->clear();
}
void RPGGameMode::addQuest(WinCondition condition)
{
    quests->push_back(condition);
}

bool RPGGameMode::checkWinCondition()
{
    return false;
    /*   For now, ignore quests. Reimplement when quest givers and rewards are added
    for (int i = 0; i < quests->size(); i++)
       {
           if (!checkWinCondition(quests->at(i)))
           {
               return false;
           }
       }
       return true;*/
}

bool RPGGameMode::operator==(IGameMode const &other) const
{
    if (dynamic_cast<const RPGGameMode *>(&other))
        return true;
    return false;
}
bool RPGGameMode::hasHealth()
{
    return true;
}