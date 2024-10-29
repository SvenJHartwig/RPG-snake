#pragma once

#include "iGameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include "../TextRenderer/TextRenderer.h"
#include "elements/scene.h"

class GlView : public IGameView
{
private:
    IGameController *gameController;
    font_data *fd;
    GLFWwindow *window;
    Scene *currentScene;
    Scene *mainMenu;

public:
    void renderingLoop();
    int init();
    void showUI(int eatenFoods);
    void showGrid(vector<string> *, int grid_size_x, int grid_size_y);
    void gameStateChanged(GameState game_state);
    void initMainMenu();
    IGameController *getGameController() { return gameController; }
    void setGameController(IGameController *gc) { this->gameController = gc; }
    Scene *getCurrentScene() { return currentScene; }
    void setCurrentScene(Scene *current_scene) { this->currentScene = current_scene; }
};