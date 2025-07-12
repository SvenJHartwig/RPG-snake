#pragma once

#include "mob.h"
#include <memory>

class IDialogCondition
{
public:
    virtual bool evaluate(int dialogState) = 0;
    virtual void serialize(std::ofstream *outFile) = 0;
};

class DialogConditionIsState : public IDialogCondition
{
public:
    bool evaluate(int dialogState) override;
    DialogConditionIsState(int stateToReach);
    void serialize(std::ofstream *outFile) override;

private:
    int stateToReach;
};

class DialogConditionQuestFinished : public IDialogCondition
{
public:
    bool evaluate(int dialogState) override;
    DialogConditionQuestFinished(std::string questID);
    void serialize(std::ofstream *outFile) override;

private:
    std::string questID;
};

class IDialogAction
{
public:
    virtual void execute() = 0;
    virtual void serialize(std::ofstream *outFile) = 0;
};

class DialogActionShowText : public IDialogAction
{
public:
    void execute() override;
    DialogActionShowText(std::string text);
    void serialize(std::ofstream *outFile) override;

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
    void serialize(std::ofstream *outFile) override;

private:
    int targetState;
    IStateReceiver *receiver;
};

class DialogActionAddQuest : public IDialogAction
{
public:
    void execute() override;
    DialogActionAddQuest(Quest *quest);
    void serialize(std::ofstream *outFile) override;

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
    DialogState();
    std::vector<IDialogAction *> *getActions();
    void serialize(std::ofstream *outFile);

private:
    std::vector<IDialogCondition *> *conditions;
    std::vector<IDialogAction *> *actions;
};

class NPC_Dialog : public IStateReceiver
{
public:
    void changeState(int state);
    int getState();
    NPC_Dialog();
    NPC_Dialog(std::vector<DialogState *> *states);
    void invoke();
    std::vector<DialogState *> *getStates();
    void serialize(std::ofstream *outFile);

private:
    int dialogState;
    std::vector<DialogState *> *states;
};

class NPC : public Mob
{
public:
    void snakeOnElement(IGridController *controller) override;
    void snakeMovedAway(IGridController *controller) override;
    void tick() override;
    NPC(int pos_x, int pos_y);
    ~NPC();
    void createSampleDialog();
    void setDialog(NPC_Dialog *dialog);
    void serialize(std::ofstream *outFile) override;
    void loadDialogFromFile(std::ifstream *inFile);

private:
    std::shared_ptr<NPC_Dialog> dialog;
    bool stillOnElement;
    Quest *quest;
};
