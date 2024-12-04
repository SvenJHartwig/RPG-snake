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
    IRenderEngine *engine;
    IGameController *gameController;
    Scene *mainMenu;
    Scene *inGame;
    Scene *gameOver;
    Scene *win;
    bool initialized = false;

public:
    int init();
    void gameStateChanged(GameState game_state);
    Scene *getMainMenu() { return mainMenu; }
    Scene *getInGameScene() { return inGame; }
    Scene *getGameOverScene() { return gameOver; }
    void initMainMenu();
    void initGameScene();
    void initGameOverScene();
    void initWinScene();
    IGameController *getGameController() { return gameController; }
    void setGameController(IGameController *gc) { this->gameController = gc; }
    void setEngine(IRenderEngine *engine) { this->engine = engine; }
    IRenderEngine *getEngine() { return engine; }
    bool isInitialized() { return initialized; }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    void setScore(int count);
    void setGrid(vector<vector<Sprite> *> *grid);
};