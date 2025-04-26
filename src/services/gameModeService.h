#pragma once
#include "../model/gameMode.h"
#include <memory>

class GameModeService
{
public:
    static void setInstance(std::shared_ptr<IGameMode> instance);

    static std::shared_ptr<IGameMode> get();

private:
    static std::shared_ptr<IGameMode> &getInstance();
};
