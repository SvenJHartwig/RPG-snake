#include "../model/grid.h"

enum SpeedSetting
{
    l1 = 800000,
    l2 = 700000,
    l3 = 600000,
    l4 = 450000,
    l5 = 300000,
    l6 = 200000,
};

enum GameState
{
    MAIN_MENU,
    IN_GAME,
};

class IGameController
{
public:
    virtual void reactOnInput(char input) = 0;
    virtual void setWindowClosed(bool closed) = 0;
    virtual Grid getGrid() = 0;
    virtual int getScore() = 0;
    virtual GameState getGameState() = 0;
};