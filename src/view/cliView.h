#include "iGameView.h"

class CliView : public IGameView
{
public:
    void setGameController(IGameController *gc) override;
    int init();
    void showGrid(char **grid, int grid_size_x, int grid_size_y);
};