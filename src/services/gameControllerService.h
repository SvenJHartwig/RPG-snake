#pragma once
#include "../controller/gameController.h"
#include <memory>

class GameControllerService
{
public:
    static void setInstance(std::shared_ptr<GameController> instance);

    static std::shared_ptr<GameController> get();

private:
    static std::shared_ptr<GameController> &getInstance();
};
