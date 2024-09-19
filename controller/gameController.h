#include "gridController.h"
#include "../view/iGameView.h"

class GameController
{
private:
    Grid grid;
    GridController gridController;
    IGameView *view;
    void reactOnInput(char input);

public:
    void setView(IGameView *view);
    void mainLoop();
};