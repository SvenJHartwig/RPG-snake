#pragma once

#include "mob.h"

class IDialogCondition
{
public:
    virtual bool evaluate(int dialogState) = 0;
};

class DialogConditionIsState : public IDialogCondition
{
public:
    bool evaluate(int dialogState) override;
    DialogConditionIsState(int stateToReach);

private:
    int stateToReach;
};

class DialogConditionQuestFinished : public IDialogCondition
{
public:
    bool evaluate(int dialogState) override;
    DialogConditionQuestFinished(std::string questID);

private:
    std::string questID;
};

class IDialogAction
{
public:
    virtual void execute() = 0;
};

class DialogActionShowText : public IDialogAction
{
public:
    void execute() override;
    DialogActionShowText(std::string text);

private:
    std::string text;
};

class DialogActionChangeDialogState : public IDialogAction
{
public:
    void execute() override;
};

class DialogActionAddQuest : public IDialogAction
{
public:
    void execute() override;
};

class DialogState
{
public:
    bool evaluate(int dialogState);
    void execute();
    DialogState(std::vector<IDialogCondition *> *conditions,
                std::vector<IDialogAction *> *actions);

private:
    std::vector<IDialogCondition *> *conditions;
    std::vector<IDialogAction *> *actions;
};

class NPC_Dialog
{
public:
private:
    int dialogState;
    std::vector<DialogState *> states;
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
