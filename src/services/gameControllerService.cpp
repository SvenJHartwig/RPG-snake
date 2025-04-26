#include "gameControllerService.h"

void GameControllerService::setInstance(std::shared_ptr<GameController> instance)
{
    getInstance() = instance;
}

std::shared_ptr<GameController> GameControllerService::get()
{
    return getInstance();
}

std::shared_ptr<GameController> &GameControllerService::getInstance()
{
    static std::shared_ptr<GameController> instance = nullptr;
    return instance;
}
