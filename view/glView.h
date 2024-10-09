#pragma once

#include "iGameView.h"
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class GlView : public IGameView
{
private:
    IGameController *gameController;
    FT_Face face;
    FT_Library ft;

public:
    void setGameController(IGameController *gc);
    void renderingLoop(GLFWwindow *window);
    int init();
    void showUI(int eatenFoods);
    void showGrid(char **grid, int grid_size_x, int grid_size_y);
};