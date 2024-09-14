#include <vector>
#include "snake.h"

class Grid
{
    private:
        char **grid;
        int grid_size_x;
        int grid_size_y;

    public:
        Grid();
        ~Grid();
        void setGrid(char **grid);
        char **getGrid();
        int getGridSizeX();
        int getGridSizeY();
};
