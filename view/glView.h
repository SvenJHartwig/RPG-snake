#pragma once

#include "iGameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../TextRenderer/TextRenderer.h"

class GlView : public IGameView
{
private:
    IGameController *gameController;
    font_data *fd;

public:
    void setGameController(IGameController *gc);
    void renderingLoop(GLFWwindow *window);
    int init();
    void showUI(int eatenFoods);
    void showGrid(char **grid, int grid_size_x, int grid_size_y);
};