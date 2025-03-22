#pragma once

#include "mob.h"

class NPC : public Mob
{
public:
    void snakeOnElement(IGridController *controller) override;
    void serialize(std::ofstream *outFile) override;
    void tick() override;
    NPC(int pos_x, int pos_y);
    ~NPC();
};