#include "../model/grid.h"

class GridController{
    private:
        Snake snake;
        Food *food;
        bool game_over = false;
        
        void checkGameOver(Grid *grid);
        bool anyFoodOnThisField(int i, int j);
        bool anyMovedBodypartOnThisField(int i, int j);
        bool anyBodypartOnThisField(int i, int j);

    public:
        GridController();
        ~GridController();
        char **updateGrid(Grid *grid);
        void moveSnakeRight();
        void moveSnakeLeft();
        void moveSnakeUp();
        void moveSnakeDown();
        Snake *getSnake();
        bool isGameOver();
};
