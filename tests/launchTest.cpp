#include "../src/view/engine/renderEngine.h"
#include "../src/view/glView.h"
#include "../src/view/engine/elements/text.h"
#include "../src/view/engine/elements/spriteGrid.h"
#include <chrono>
#include <thread>
#include "testClasses.h"

using std::vector, std::string;

TEST_CASE("Initialize OpenGL (Engine)")
{
    RenderEngine *engine = new RenderEngine();
    REQUIRE(engine->init() == 0);
    glfwTerminate();
}

TEST_CASE("Initialize OpenGL (View)")
{
    using namespace std::this_thread;
    using namespace std::chrono;

    GlView *view = new GlView();
    view->setGameController(new TestGameController());
    REQUIRE(view->init() == 0);
    // Wait a bit so the window can be opened
    while (!view->isInitialized())
    {
        sleep_for(milliseconds(5));
    }
    view->gameStateChanged(GAME_OVER);
    view->gameStateChanged(MAIN_MENU);
    view->gameStateChanged(MAIN_MENU);
    view->gameStateChanged(IN_GAME);
    view->gameStateChanged(GAME_OVER);
    view->setScore(2);
    REQUIRE(static_cast<Text *>(view->getInGameScene()->scene_elements->at(0))->text.compare("Score: 2") == 0);
    const std::vector<std::string> *grid = new std::vector<std::string>();
    std::vector<std::vector<Sprite> *> *spriteGrid = GridController(new TestEatListener()).getSpriteVector();
    view->setGrid(spriteGrid);
    REQUIRE(static_cast<SpriteGrid *>(view->getInGameScene()->scene_elements->at(2))->getGrid() == spriteGrid);
    view->gameStateChanged(WIN);
    REQUIRE(static_cast<SpriteGrid *>(view->getInGameScene()->scene_elements->at(2))->getGrid() == spriteGrid);
    view->gameStateChanged(MAIN_MENU);
    SEngine::engine_key_callback(view->getEngine()->getWindow(), GLFW_KEY_P, 0, GLFW_RELEASE, 0);
    REQUIRE(!static_cast<TestGameController *>(view->getGameController())->calledP);
    SEngine::engine_key_callback(view->getEngine()->getWindow(), GLFW_KEY_P, 0, GLFW_PRESS, 0);
    REQUIRE(static_cast<TestGameController *>(view->getGameController())->calledP);
    glfwSetWindowShouldClose(view->getEngine()->getWindow(), true);
    sleep_for(milliseconds(500));
}

TEST_CASE("Main Menu is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initMainMenu();
    Scene *mainMenu = view->getMainMenu();
    REQUIRE(mainMenu->scene_elements->size() == 3);
    REQUIRE(mainMenu->scene_elements->at(0)->getPosXTopLeft() == 432);
    glfwTerminate();
}

TEST_CASE("Game scene is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initGameScene();
    Scene *inGame = view->getInGameScene();
    REQUIRE(inGame->scene_elements->size() == 4);
    REQUIRE(inGame->scene_elements->at(0)->getPosXTopLeft() == 0);
    REQUIRE(inGame->scene_elements->at(0)->getPosYTopLeft() == 0);
    REQUIRE(inGame->scene_elements->at(1)->getPosXTopLeft() == 192);
    REQUIRE(inGame->scene_elements->at(1)->getPosYTopLeft() == 80);
    REQUIRE(inGame->scene_elements->at(2)->getPosXTopLeft() == 192);
    REQUIRE(inGame->scene_elements->at(2)->getPosYTopLeft() == 80);
    glfwTerminate();
}

TEST_CASE("Game over scene is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initGameOverScene();
    Scene *gameOver = view->getGameOverScene();
    REQUIRE(gameOver->scene_elements->size() == 4);
    REQUIRE(gameOver->scene_elements->at(0)->getPosXTopLeft() == 0);
    REQUIRE(gameOver->scene_elements->at(0)->getPosYTopLeft() == 0);
    REQUIRE(gameOver->scene_elements->at(1)->getPosXTopLeft() == 192);
    REQUIRE(gameOver->scene_elements->at(1)->getPosYTopLeft() == 80);
    glfwTerminate();
}