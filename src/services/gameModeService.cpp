#include "gameModeService.h"

void GameModeService::setInstance(std::shared_ptr<IGameMode> instance)
{
    getInstance() = instance;
}

std::shared_ptr<IGameMode> GameModeService::get()
{
    return getInstance();
}

std::shared_ptr<IGameMode> &GameModeService::getInstance()
{
    static std::shared_ptr<IGameMode> instance = nullptr;
    return instance;
}
