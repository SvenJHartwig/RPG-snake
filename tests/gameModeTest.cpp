#include "testClasses.h"

TEST_CASE("Switch game modes")
{
    GameController *gameController = new GameController();
    gameController->setGameMode(INFINITE);
    REQUIRE(*(gameController->getGameMode()) == InfiniteGameMode(gameController));
    gameController->setGameMode(RPG);
    REQUIRE(*(gameController->getGameMode()) == RPGGameMode(gameController));
}