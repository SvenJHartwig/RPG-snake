#include "gameMode.h"
#include "string.h"

InfiniteGameMode::InfiniteGameMode() {}

void InfiniteGameMode::clearQuests() {}
void InfiniteGameMode::addQuest(std::string name, WinCondition *condition) {}
void InfiniteGameMode::addQuest(Quest *quest) {}

std::vector<Quest *> *InfiniteGameMode::getQuests()
{
    return new std::vector<Quest *>();
}
std::tuple<bool, Quest *> InfiniteGameMode::getQuest(std::string questID)
{
    return std::make_tuple(false, new Quest("", new WinCondition(NONE, 0)));
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

RPGGameMode::RPGGameMode() {}

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
std::tuple<bool, Quest *> RPGGameMode::getQuest(std::string questID)
{
    for (Quest *quest : *quests)
    {
        if (quest->getName().compare(questID) == 0)
        {
            return std::make_tuple(true, quest);
        }
    }
    return std::make_tuple(false, new Quest("", new WinCondition(NONE, 0)));
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
