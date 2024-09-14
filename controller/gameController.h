#include "gridController.h"
#include "../view/cliView.h"

class GameController{
    private:
        Grid grid;
        GridController gridController;
        CliView view;
    public:
        void mainLoop();
};