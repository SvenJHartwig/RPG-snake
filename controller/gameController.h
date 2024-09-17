#include "gridController.h"
#include "../view/cliView.h"

class GameController{
    private:
        Grid grid;
        GridController gridController;
        CliView view;
        void reactOnInput(char input);
    public:
        void mainLoop();
};