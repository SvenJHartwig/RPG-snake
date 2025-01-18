#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class GridElement
{
protected:
    int pos_x;
    int pos_y;

public:
    virtual void serialize(std::ofstream *outFile) = 0;
    int getPosX();
    int getPosY();
    void setPosX(int pos);
    void setPosY(int pos);
};

class Ground : public GridElement
{
public:
    Ground(int pos_x, int pos_y);
    void serialize(std::ofstream *outFile) override;
};

class Wall : public GridElement
{
public:
    Wall(int pos_x, int pos_y);
    void serialize(std::ofstream *outFile) override;
};