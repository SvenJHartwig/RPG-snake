#include "iGameView.h"
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"

class GlView : public IGameView
{
private:
    IGameController *gameController;

public:
    void setGameController(IGameController *gc);
    void renderingLoop(GLFWwindow *window);
    int init();
    void showGrid(char **grid, int grid_size_y);
};