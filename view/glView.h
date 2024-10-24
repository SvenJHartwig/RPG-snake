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
    void setGameController(IGameController *gc);
    void renderingLoop();
    int init();
    void showUI(int eatenFoods);
    void showGrid(char **grid, int grid_size_x, int grid_size_y);
    void gameStateChanged(GameState game_state);
    void setCurrentScene(Scene *current_scene);
    void initMainMenu();
    IGameController *getGameController() { return gameController; }
    Scene *getCurrentScene() { return currentScene; }
};