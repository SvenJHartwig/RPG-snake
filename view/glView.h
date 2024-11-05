#pragma once

#include "iGameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include "../TextRenderer/TextRenderer.h"
#include "engine/elements/scene.h"
#include "engine/iRenderEngine.h"

class GlView : public IGameView
{
private:
    IRenderEngine *engine;
    IGameController *gameController;
    Scene *mainMenu;
    Scene *inGame;
    bool initialized = false;

public:
    void renderingLoop();
    int init();
    void gameStateChanged(GameState game_state);
    Scene *getMainMenu() { return mainMenu; }
    Scene *getInGameScene() { return inGame; }
    void initMainMenu();
    void initGameScene();
    IGameController *getGameController() { return gameController; }
    void setGameController(IGameController *gc) { this->gameController = gc; }
    void setEngine(IRenderEngine *engine) { this->engine = engine; }
    bool isInitialized() { return initialized; }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    void setScore(int count);
    void setGrid(vector<string> *grid);
};