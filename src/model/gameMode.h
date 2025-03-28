#pragma once

#include "winCondition.h"
#include "../controller/iGameController.h"
#include <vector>
#include "quest.h"

enum GameModeEnum
{
    INFINITE,
    RPG
};

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

class GameModeFactory
{
private:
    GameModeFactory() {}

public:
    static IGameMode *createGameMode(GameModeEnum mode, IGameController *controller);
};

class InfiniteGameMode : public IGameMode
{
public:
    InfiniteGameMode(IGameController *controller);
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
    IGameController *controller;
    std::vector<Quest *> *quests = new std::vector<Quest *>();

public:
    RPGGameMode(IGameController *controller);
    void clearQuests() override;
    void addQuest(std::string name, WinCondition *condition) override;
    void addQuest(Quest *quest) override;
    std::vector<Quest *> *getQuests() override;
    bool operator==(IGameMode const &other) const override;
    bool hasHealth() override;
};