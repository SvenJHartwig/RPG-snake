#include "npc.h"
#include "../services/gameModeService.h"

void NPC::snakeOnElement(IGridController *controller)
{
    if (dialogState == 0)
    {
        controller->showText("Please get 10 points");
        GameModeService::get()->addQuest(quest);
    }
}
void NPC::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&"N"), sizeof(char));
    outFile->write(reinterpret_cast<const char *>(&pos_x), sizeof(pos_x));
    outFile->write(reinterpret_cast<const char *>(&pos_y), sizeof(pos_y));
}
void NPC::tick() {}
NPC::NPC(int pos_x, int pos_y)
{
    dialogState = 0;
    quest = new Quest("NPC Quest", new WinCondition(WinConType::SCORE, 10));
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
NPC::~NPC()
{
}
