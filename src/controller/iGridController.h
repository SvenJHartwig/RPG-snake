#pragma once

#include <string>

class IGridController
{
public:
    virtual void loadLevel(std::string path) = 0;
};