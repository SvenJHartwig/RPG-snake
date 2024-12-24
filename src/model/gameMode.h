#pragma once

enum GameModeEnum
{
    INFINITE,
    RPG
};

class IGameMode
{
public:
    virtual bool operator==(IGameMode const &other) const = 0;
};

class GameModeFactory
{
public:
    static IGameMode *createGameMode(GameModeEnum mode);
};

class InfiniteGameMode : public IGameMode
{
public:
    InfiniteGameMode();
    bool operator==(IGameMode const &other) const;
};

class RPGGameMode : public IGameMode
{
public:
    RPGGameMode();
    bool operator==(IGameMode const &other) const;
};