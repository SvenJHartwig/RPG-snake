#pragma once

#include "gridElement.h"

class Teleporter : public GridElement
{
private:
    int targetPosX;
    int targetPosY;
    std::string path;

public:
    Teleporter(int pos_x, int pos_y, std::string path, int targetPosX, int targetPosY);
    void snakeOnElement(IGridController *controller) override;
    void serialize(std::ofstream *outFile) override;
};