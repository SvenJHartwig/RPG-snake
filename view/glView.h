#pragma once

#include "iGameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include "../TextRenderer/TextRenderer.h"
#include "engine/elements/scene.h"
#include "engine/renderEngine.h"

class GlView : public IGameView
{
private:
    RenderEngine *engine;
    IGameController *gameController;
    Scene *mainMenu;
    Scene *inGame;

public:
    void renderingLoop();
    int init();
    void showUI(int eatenFoods);
    void showGrid(vector<string> *, int grid_size_x, int grid_size_y);
    void gameStateChanged(GameState game_state);
    Scene *getMainMenu() { return mainMenu; }
    void initMainMenu();
    void initGameScene();
    IGameController *getGameController() { return gameController; }
    void setGameController(IGameController *gc) { this->gameController = gc; }
};