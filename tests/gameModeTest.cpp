#include "testClasses.h"
#include "../src/services/gameModeService.h"
#include "../src/services/gameControllerService.h"
#include "../src/model/gameMode.h"
#include "../src/model/npc.h"

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

TEST_CASE("NPC interaction")
{
    GameControllerService::setInstance(std::make_shared<GameController>());
    GameModeService::setInstance(std::make_shared<RPGGameMode>());
    GameController *gameController = GameControllerService::get().get();
    gameController->setView(new TestView());
    gameController->setSoundController(new TestSoundController());
    GridController *gridController = new GridController(gameController);
    NPC *npc = new NPC(0, 0);
    npc->snakeOnElement(gridController);
    REQUIRE(GameModeService::get()->getQuests()->size() == 1);
    gameController->eat(true);
    gameController->eat(true);
    gameController->eat(true);
    gameController->eat(true);
    gameController->eat(true);
    gameController->eat(true);
    npc->snakeOnElement(gridController);
    REQUIRE(!GameModeService::get()->getQuests()->at(0)->getIsFinished());
    npc->snakeMovedAway(gridController);
    REQUIRE(!GameModeService::get()->getQuests()->at(0)->getIsFinished());
    npc->snakeOnElement(gridController);
    REQUIRE(GameModeService::get()->getQuests()->at(0)->getIsFinished());
}

TEST_CASE("Quests only start counting when they're active")
{
    GameControllerService::setInstance(std::make_shared<GameController>());
    GameModeService::setInstance(std::make_shared<RPGGameMode>());
    GameController *gameController = GameControllerService::get().get();
    gameController->eat(true);
}