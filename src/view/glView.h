#pragma once

#include "iGameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include "engine/elements/scene.h"
#include "engine/iRenderEngine.h"

class GlView : public IGameView
{
private:
    SEngine::IRenderEngine *engine;
    IGameController *gameController;
    SEngine::Scene *mainMenu;
    SEngine::Scene *inGame;
    SEngine::Scene *gameOver;
    SEngine::Scene *win;
    bool initialized = false;

public:
    int init();
    void gameStateChanged(GameState game_state);
    SEngine::Scene *getMainMenu() { return mainMenu; }
    SEngine::Scene *getInGameScene() { return inGame; }
    SEngine::Scene *getGameOverScene() { return gameOver; }
    void initMainMenu();
    void initGameScene();
    void initGameOverScene();
    void initWinScene();
    IGameController *getGameController() { return gameController; }
    void setGameController(IGameController *gc) { this->gameController = gc; }
    void setEngine(SEngine::IRenderEngine *engine) { this->engine = engine; }
    SEngine::IRenderEngine *getEngine() { return engine; }
    bool isInitialized() { return initialized; }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    void setScore(int count);
    void setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid);
};