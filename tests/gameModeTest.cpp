#include "testClasses.h"
#include "../src/services/gameModeService.h"
#include "../src/model/gameMode.h"

TEST_CASE("Switch game modes")
{
    GameController *gameController = new GameController();
    GameModeService::setInstance(std::make_shared<InfiniteGameMode>());
    REQUIRE(*(GameModeService::get()) == InfiniteGameMode());
    GameModeService::setInstance(std::make_shared<RPGGameMode>());
    REQUIRE(*(GameModeService::get()) == RPGGameMode());
}

TEST_CASE("Create WinConditions")
{
    WinCondition winCon = WinCondition(SCORE, -1);
    REQUIRE(!(winCon == WinCondition(SCORE, 0)));
    REQUIRE(winCon != WinCondition(SCORE, 0));
    REQUIRE(winCon != WinCondition(TIME, -1));
    REQUIRE(winCon != WinCondition(NONE, -1));
    REQUIRE(winCon == WinCondition(SCORE, -1));
}

TEST_CASE("Movement in RPG mode")
{
    GameController *gameController = new GameController();
    GameModeService::setInstance(std::make_shared<RPGGameMode>());
    gameController->reactOnInput(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == 'd');
    gameController->reactOnKeyReleased(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == ' ');
    GameModeService::setInstance(std::make_shared<InfiniteGameMode>());
    gameController->reactOnInput(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == 'd');
    gameController->reactOnKeyReleased(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == 'd');
}
