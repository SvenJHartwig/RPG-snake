#include "iGameView.h"

class CliView : public IGameView
{
public:
    int init();
    void showGrid(char **grid, int grid_size_y);
};