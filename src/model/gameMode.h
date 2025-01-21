#pragma once

#include "winCondition.h"
#include "../controller/iGameController.h"
#include <vector>

enum GameModeEnum
{
    INFINITE,
    RPG
};

class IGameMode
{
public:
    virtual void clearQuests() = 0;
    virtual void addQuest(WinCondition condition) = 0;
    virtual bool operator==(IGameMode const &other) const = 0;
    virtual bool checkWinCondition() = 0;
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
    void addQuest(WinCondition condition) override;
    bool checkWinCondition() override;
    bool operator==(IGameMode const &other) const override;
    bool hasHealth() override;
};

class RPGGameMode : public IGameMode
{
private:
    IGameController *controller;
    std::vector<WinCondition> *quests = new std::vector<WinCondition>();
    bool checkWinCondition(WinCondition condition);

public:
    RPGGameMode(IGameController *controller);
    void clearQuests() override;
    void addQuest(WinCondition condition) override;
    bool checkWinCondition() override;
    bool operator==(IGameMode const &other) const override;
    bool hasHealth() override;
};