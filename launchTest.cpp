#include <catch2/catch.hpp>
#include "view/engine/renderEngine.h"
#include "view/glView.h"
#include "view/engine/iRenderEngine.h"
#include "view/engine/elements/text.h"
#include "view/engine/elements/spriteGrid.h"
#include "controller/iGameController.h"
#include <chrono>
#include <thread>

class TestGameController : public IGameController
{
public:
    bool calledP = false;
    GameState getGameState() { return MAIN_MENU; };
    Grid getGrid()
    {
        Grid grid;
        return grid;
    }
    int getScore() { return 0; }
    void reactOnInput(char input)
    {
        if (input == 'p')
            calledP = true;
    }
    void setWindowClosed(bool closed) {}
};

class TestRenderEngine : public IRenderEngine
{
public:
    IEngineCallback *getEngineCallback() { return new TestGameController(); }
    void setEngineCallback(IEngineCallback *callback) {}
    Scene *getCurrentScene() { return new Scene(); }
    GLFWwindow *getWindow()
    {
        glfwInit();
        return glfwCreateWindow(1024, 768, "Snake", NULL, NULL);
    }
    void setCurrentScene(Scene *currentScene) {}
    void renderingLoop() {}
    int init() { return 0; }
};

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
    REQUIRE(((Text *)view->getInGameScene()->scene_elements->at(0))->text.compare("Score: 2") == 0);
    std::vector<std::string> *grid = new std::vector<std::string>();
    /*   view->setGrid(grid);
    REQUIRE(((SpriteGrid *)view->getInGameScene()->scene_elements->at(1))->getGrid() == grid);
    view->gameStateChanged(WIN);
    REQUIRE(((SpriteGrid *)view->getInGameScene()->scene_elements->at(1))->getGrid() == grid);
    view->gameStateChanged(MAIN_MENU);
    engine_key_callback(view->getEngine()->getWindow(), GLFW_KEY_P, 0, GLFW_RELEASE, 0);
    REQUIRE(!((TestGameController *)view->getGameController())->calledP);
    engine_key_callback(view->getEngine()->getWindow(), GLFW_KEY_P, 0, GLFW_PRESS, 0);
    REQUIRE(((TestGameController *)view->getGameController())->calledP);
    glfwSetWindowShouldClose(view->getEngine()->getWindow(), true);
    sleep_for(milliseconds(500));*/
}

TEST_CASE("Main Menu is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initMainMenu();
    Scene *mainMenu = view->getMainMenu();
    REQUIRE(mainMenu->scene_elements->size() == 3);
    REQUIRE(mainMenu->scene_elements->at(0)->getPosXTopLeft() == 472);
    glfwTerminate();
}

TEST_CASE("Game scene is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initGameScene();
    Scene *inGame = view->getInGameScene();
    REQUIRE(inGame->scene_elements->size() == 2);
    REQUIRE(inGame->scene_elements->at(0)->getPosXTopLeft() == 0);
    REQUIRE(inGame->scene_elements->at(0)->getPosYTopLeft() == 20);
    REQUIRE(inGame->scene_elements->at(1)->getPosXTopLeft() == 192);
    REQUIRE(inGame->scene_elements->at(1)->getPosYTopLeft() == 80);
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
    REQUIRE(gameOver->scene_elements->at(0)->getPosYTopLeft() == 20);
    REQUIRE(gameOver->scene_elements->at(1)->getPosXTopLeft() == 192);
    REQUIRE(gameOver->scene_elements->at(1)->getPosYTopLeft() == 80);
    glfwTerminate();
}