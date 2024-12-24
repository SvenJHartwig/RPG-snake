#include "gameMode.h"

IGameMode *GameModeFactory::createGameMode(GameModeEnum mode)
{
    switch (mode)
    {
    case INFINITE:
        return new InfiniteGameMode();
    case RPG:
        return new RPGGameMode();
    }
}

InfiniteGameMode::InfiniteGameMode()
{
}

bool InfiniteGameMode::operator==(IGameMode const &other) const
{
    if (dynamic_cast<const InfiniteGameMode *>(&other))
        return true;
    return false;
}

RPGGameMode::RPGGameMode()
{
}

bool RPGGameMode::operator==(IGameMode const &other) const
{
    if (dynamic_cast<const RPGGameMode *>(&other))
        return true;
    return false;
}