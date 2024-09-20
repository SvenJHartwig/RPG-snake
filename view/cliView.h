#include "iGameView.h"

class CliView : public IGameView
{
public:
    void setGameController(IGameController *gc);
    int init();
    void showGrid(char **grid, int grid_size_y);
};