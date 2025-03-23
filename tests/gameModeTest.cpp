#include "testClasses.h"

TEST_CASE("Switch game modes")
{
    GameController *gameController = new GameController();
    gameController->setGameMode(INFINITE);
    REQUIRE(*(gameController->getGameMode()) == InfiniteGameMode(gameController));
    gameController->setGameMode(RPG);
    REQUIRE(*(gameController->getGameMode()) == RPGGameMode(gameController));
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
    gameController->setGameMode(RPG);
    gameController->reactOnInput(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == 'd');
    gameController->reactOnKeyReleased(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == ' ');
    gameController->setGameMode(INFINITE);
    gameController->reactOnInput(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == 'd');
    gameController->reactOnKeyReleased(GLFW_KEY_RIGHT);
    REQUIRE(gameController->getLastInput() == 'd');
}