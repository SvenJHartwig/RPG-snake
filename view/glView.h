#include "iGameView.h"

class GlView : public IGameView
{
public:
    int init();
    void showGrid(char **grid, int grid_size_y);
};