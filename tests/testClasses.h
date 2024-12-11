#include <string.h>
#include <iostream>
#include <catch2/catch.hpp>
#include "../src/controller/gridController.h"
#include "../src/controller/gameController.h"
#include "../src/controller/iGameController.h"
#include "../src/controller/iEatListener.h"
#include "../src/view/engine/iRenderEngine.h"

using std::vector, std::string;

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
    void eat(bool isSpecial) {}
};

class TestView : public IGameView
{
    void setGameController(IGameController *gc) {}
    void renderingLoop() {}
    int init() { return 0; }
    void showGrid(vector<string> *grid, int grid_size_x, int grid_size_y) {}
    void gameStateChanged(GameState game_state) {}
    void setCurrentScene(Scene *current_scene) {}
    void setScore(int count) {}
    void setGrid(vector<vector<Sprite> *> *grid) {}
};

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
