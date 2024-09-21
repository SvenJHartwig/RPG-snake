#include "../model/grid.h"

class IGameController
{
public:
    virtual void setWindowClosed(bool closed) = 0;
    virtual Grid getGrid() = 0;
};