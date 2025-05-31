#pragma once

#include "mob.h"

class IDialogCondition
{
public:
    virtual bool evaluate() = 0;
};

class DialogConditionIsState
{
public:
    bool evaluate();
};

class DialogConditionQuestFinished
{
public:
    bool evaluate();
};

class IDialogAction
{
public:
    virtual bool execute() = 0;
};

class DialogActionShowText
{
public:
    bool execute();
};

class DialogActionChangeDialogState
{
public:
    bool execute();
};

class DialogActionAddQuest
{
public:
    bool execute();
};

class DialogState
{
public:
    bool evaluate();
    void execute();

private:
    std::vector<IDialogCondition> conditions;
    std::vector<IDialogAction> actions;
};

class NPC_Dialog
{
public:
private:
    std::vector<DialogState> states;
};

class NPC : public Mob
{
public:
    void snakeOnElement(IGridController *controller) override;
    void snakeMovedAway(IGridController *controller) override;
    void serialize(std::ofstream *outFile) override;
    void tick() override;
    NPC(int pos_x, int pos_y);
    ~NPC();

private:
    bool stillOnElement;
    int dialogState;
    Quest *quest;
};
