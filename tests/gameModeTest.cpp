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
    gameController->setSoundController(new TestSoundController());
    gameController->setView(new TestView());
    gameController->eat(true);
    // TODO EXPAND TEST
}

TEST_CASE("Dialog Test")
{
    DialogConditionIsState *condition1 = new DialogConditionIsState(2);
    REQUIRE(!condition1->evaluate(1));
    REQUIRE(condition1->evaluate(2));
    REQUIRE(!condition1->evaluate(3));
    DialogConditionQuestFinished *condition2 = new DialogConditionQuestFinished("Test");
    REQUIRE(!condition2->evaluate(1));
    GameModeService::setInstance(std::make_shared<RPGGameMode>());
    GameModeService::get()->addQuest(new Quest("Test", new WinCondition(SCORE, 2)));
    GameControllerService::setInstance(std::make_shared<GameController>());
    GameController *gameController = GameControllerService::get().get();
    gameController->setSoundController(new TestSoundController());
    TestView *view = new TestView();
    gameController->setView(view);
    gameController->eat(true);
    REQUIRE(condition2->evaluate(1));

    DialogState *state1 = new DialogState(new std::vector<IDialogCondition *>(1, condition1), new std::vector<IDialogAction *>());
    REQUIRE(state1->evaluate(2));
    REQUIRE(!state1->evaluate(1));

    DialogActionShowText *action1 = new DialogActionShowText("Test");
    action1->execute();
    REQUIRE(view->showDialogText.compare("Test") == 0);

    NPC_Dialog *dialog = new NPC_Dialog(new std::vector<DialogState *>(1, state1));
    REQUIRE(dialog->getState() == 0);
    DialogActionChangeDialogState *action2 = new DialogActionChangeDialogState(3, dialog);
    action2->execute();
    REQUIRE(dialog->getState() == 3);
}