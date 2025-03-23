#include <string.h>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "../src/controller/gridController.h"
#include "../src/controller/gameController.h"
#include "../src/controller/iGameController.h"
#include "../src/controller/iEatListener.h"
#include "../src/view/engine/iRenderEngine.h"
#include "../src/view/engine/elements/button.h"
#include "../src/view/engine/elements/text.h"
#include "../src/view/engine/renderEngine.h"
#include "../src/controller/iSoundController.h"

using SEngine::RenderData, SEngine::Button, SEngine::IRenderEngine, SEngine::RenderEngine, SEngine::Text, SEngine::Sprite, SEngine::Scene, SEngine::IEngineCallback, SEngine::SpriteGrid;
using std::vector, std::string;

/*
 * Define some test implementations for the interfaces
 */

class TestGenerator : public RandomGenerator
{
    bool first = false;

public:
    int specificValue = 0;
    std::pair<int, int> getRandomPair(int max_value_x, int max_value_y, const std::set<std::pair<int, int>> &exclusions) override
    {
        return std::pair<int, int>(9, 5);
    }
    int getRandom(int max_value) override
    {
        if (specificValue != 0)
        {
            return specificValue;
        }
        if (!first)
        {
            first = !first;
            return 9;
        }
        return 5;
    }
};

class TestEatListener : public IEatListener
{
public:
    void eat(bool isSpecial) override {}
};

class TestView : public IGameView
{
    void setGameController(IGameController *gc) override {}
    int init() override { return 0; }
    void gameStateChanged(GameState game_state) override {}
    void setScore(int count) override {}
    void setHealth(int count) override {}
    void setGrid(vector<vector<Sprite> *> *grid) override {}
    void setQuests(string questNames) override {}
    void showDialog(std::string text) override {}
    void closeDialog() override {}
};

class TestGameController : public IGameController
{
public:
    bool calledP = false;
    GameState getGameState() override { return MAIN_MENU; };
    int getScore() override { return 0; }
    void reactOnInput(int input) override
    {
        if (input == GLFW_KEY_ENTER)
            calledP = true;
    }
    void reactOnKeyReleased(int input) override {}
    void setWindowClosed(bool closed) override {}
    long getSteps() override { return 0; }
};

class TestRenderEngine : public IRenderEngine
{
public:
    IEngineCallback *getEngineCallback() { return new TestGameController(); }
    void setEngineCallback(IEngineCallback *callback) {}
    std::vector<Scene *> *getScenes() { return new std::vector<Scene *>(); }
    GLFWwindow *getWindow()
    {
        glfwInit();
        return glfwCreateWindow(1024, 768, "Snake", NULL, NULL);
    }
    void addScene(Scene *currentScene) {}
    void renderingLoop() {}
    int init() { return 0; }
};

class TestSoundController : public ISoundController
{
public:
    bool requestedBackgroundMusic = false;
    int playBackgroundMusic(std::string path)
    {
        requestedBackgroundMusic = true;
        return 0;
    };
    int playSoundEffect(std::string path)
    {
        return 0;
    }
};