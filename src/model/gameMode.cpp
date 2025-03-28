#include "gameMode.h"
#include "string.h"

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
void InfiniteGameMode::addQuest(std::string name, WinCondition *condition) {}
void InfiniteGameMode::addQuest(Quest *quest) {}

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
void RPGGameMode::addQuest(std::string name, WinCondition *condition)
{
    quests->push_back(new Quest(name, condition));
}
void RPGGameMode::addQuest(Quest *quest)
{
    bool questAlreadyTaken = false;
    for (int questIndex = 0; questIndex < quests->size(); questIndex++)
    {
        if (quests->at(questIndex)->getName().compare(quest->getName()) == 0)
        {
            questAlreadyTaken = true;
        }
    }
    if (!questAlreadyTaken)
    {
        quests->push_back(quest);
    }
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