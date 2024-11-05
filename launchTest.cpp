#include <catch2/catch.hpp>
#include "view/engine/renderEngine.h"
#include "view/glView.h"
#include "view/engine/iRenderEngine.h"
#include <chrono>
#include <thread>

class TestRenderEngine : public IRenderEngine
{
public:
    IEngineCallback *getEngineCallback() {}
    void setEngineCallback(IEngineCallback *callback) {}
    Scene *getCurrentScene() {}
    GLFWwindow *getWindow()
    {
        return glfwCreateWindow(1024, 768, "Snake", NULL, NULL);
    }
    void setCurrentScene(Scene *currentScene) {}
    void renderingLoop() {}
    int init() {}
    font_data *getFontData()
    {
        return new font_data();
    }
};

TEST_CASE("Initialize OpenGL (Engine)")
{
    RenderEngine *engine = new RenderEngine();
    REQUIRE(engine->init() == 0);
}

TEST_CASE("Initialize OpenGL (View)")
{
    using namespace std::this_thread;
    using namespace std::chrono;

    GlView *view = new GlView();
    REQUIRE(view->init() == 0);
    // Wait a bit so the window can be opened
    while (!view->isInitialized())
    {
        sleep_for(milliseconds(5));
    }
}

TEST_CASE("Main Menu is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initMainMenu();
    Scene *mainMenu = view->getMainMenu();
    REQUIRE(mainMenu->scene_elements->size() == 3);
    REQUIRE(mainMenu->scene_elements->at(0)->getPosXTopLeft() == 472);
}

TEST_CASE("Game scene is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initGameScene();
    Scene *inGame = view->getInGameScene();
    REQUIRE(inGame->scene_elements->size() == 2);
    REQUIRE(inGame->scene_elements->at(0)->getPosXTopLeft() == 0);
    REQUIRE(inGame->scene_elements->at(0)->getPosYTopLeft() == 748);
    REQUIRE(inGame->scene_elements->at(1)->getPosXTopLeft() == 192);
    REQUIRE(inGame->scene_elements->at(1)->getPosYTopLeft() == 688);
}

TEST_CASE("Game over scene is initialized correctly")
{
    GlView *view = new GlView();
    view->setEngine(new TestRenderEngine());
    view->initGameOverScene();
    Scene *gameOver = view->getGameOverScene();
    REQUIRE(gameOver->scene_elements->size() == 4);
    REQUIRE(gameOver->scene_elements->at(0)->getPosXTopLeft() == 0);
    REQUIRE(gameOver->scene_elements->at(0)->getPosYTopLeft() == 748);
    REQUIRE(gameOver->scene_elements->at(1)->getPosXTopLeft() == 192);
    REQUIRE(gameOver->scene_elements->at(1)->getPosYTopLeft() == 688);
}