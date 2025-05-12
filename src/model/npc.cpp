#include "npc.h"
#include "../services/gameModeService.h"
#include "../services/gameControllerService.h"

void NPC::snakeOnElement(IGridController *controller)
{
    if (stillOnElement)
    {
        return;
    }
    stillOnElement = true;
    if (dialogState == 1 && quest->checkWinCondition())
    {
        controller->showText("Thanks");
        GameControllerService::get()->showQuests();
        dialogState = 2;
    }
    else if (dialogState == 1)
    {
        controller->showText("You have a quest");
    }
    if (dialogState == 0)
    {
        controller->showText("Please get 10 points");
        GameModeService::get()->addQuest(quest);
        GameControllerService::get()->showQuests();
        dialogState++;
    }
}
void NPC::snakeMovedAway(IGridController *controller)
{
    stillOnElement = false;
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
    stillOnElement = false;
    quest = new Quest("NPC Quest", new WinCondition(WinConType::SCORE, 10));
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
NPC::~NPC()
{
}
