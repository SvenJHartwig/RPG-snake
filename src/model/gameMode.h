#pragma once

#include "winCondition.h"
#include <vector>
#include "quest.h"

class IGameMode
{
public:
    virtual void clearQuests() = 0;
    virtual void addQuest(std::string name, WinCondition *condition) = 0;
    virtual void addQuest(Quest *quest) = 0;
    virtual std::vector<Quest *> *getQuests() = 0;
    virtual bool operator==(IGameMode const &other) const = 0;
    virtual bool hasHealth() = 0;
};

class InfiniteGameMode : public IGameMode
{
public:
    InfiniteGameMode();
    void clearQuests() override;
    void addQuest(std::string name, WinCondition *condition) override;
    void addQuest(Quest *quest) override;
    std::vector<Quest *> *getQuests() override;
    bool operator==(IGameMode const &other) const override;
    bool hasHealth() override;
};

class RPGGameMode : public IGameMode
{
private:
    std::vector<Quest *> *quests = new std::vector<Quest *>();

public:
    RPGGameMode();
    void clearQuests() override;
    void addQuest(std::string name, WinCondition *condition) override;
    void addQuest(Quest *quest) override;
    std::vector<Quest *> *getQuests() override;
    bool operator==(IGameMode const &other) const override;
    bool hasHealth() override;
};
