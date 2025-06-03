#pragma once

#include "mob.h"
#include <memory>

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

class IStateReceiver
{
public:
    virtual void changeState(int state) = 0;
};

class DialogActionChangeDialogState : public IDialogAction
{
public:
    void execute() override;
    DialogActionChangeDialogState(int targetState);
    void setReceiver(IStateReceiver *receiver);

private:
    int targetState;
    IStateReceiver *receiver;
};

class DialogActionAddQuest : public IDialogAction
{
public:
    void execute() override;
    DialogActionAddQuest(Quest *quest);

private:
    Quest *quest;
};

class DialogState
{
public:
    bool evaluate(int dialogState);
    void execute();
    DialogState(std::vector<IDialogCondition *> *conditions,
                std::vector<IDialogAction *> *actions);
    std::vector<IDialogAction *> *getActions();

private:
    std::vector<IDialogCondition *> *conditions;
    std::vector<IDialogAction *> *actions;
};

class NPC_Dialog : public IStateReceiver
{
public:
    void changeState(int state);
    int getState();
    NPC_Dialog(std::vector<DialogState *> *states);
    void invoke();

private:
    int dialogState;
    std::vector<DialogState *> *states;
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
    std::shared_ptr<NPC_Dialog> dialog;
    bool stillOnElement;
    Quest *quest;
};
