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
void InfiniteGameMode::addQuest(WinCondition *condition) {}

std::vector<Quest *> *InfiniteGameMode::getQuests()
{
    return new std::vector<Quest *>();
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

void RPGGameMode::clearQuests()
{
    quests->clear();
}
void RPGGameMode::addQuest(WinCondition *condition)
{
    quests->push_back(new Quest(controller, condition));
}
std::vector<Quest *> *RPGGameMode::getQuests()
{
    return quests;
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