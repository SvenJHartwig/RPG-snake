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
    DialogConditionIsState();
    void serialize(std::ofstream *outFile) override;
    void setValue(int stateToReach);

private:
    int stateToReach;
};

class DialogConditionQuestFinished : public IDialogCondition
{
public:
    bool evaluate(int dialogState) override;
    DialogConditionQuestFinished(std::string questID);
    DialogConditionQuestFinished();
    void serialize(std::ofstream *outFile) override;
    void setValue(std::string questID);

private:
    std::string questID;
};

class IDialogAction
{
public:
    virtual void execute() = 0;
    virtual void serialize(std::ofstream *outFile) = 0;
};

class IStateReceiver
{
public:
    virtual void changeState(int state) = 0;
};

class DialogActionShowText : public IDialogAction
{
public:
    void execute() override;
    DialogActionShowText(std::string text);
    DialogActionShowText();
    void serialize(std::ofstream *outFile) override;
    void setValue(std::string text);

private:
    std::string text;
};

class DialogActionChangeDialogState : public IDialogAction
{
public:
    void execute() override;
    DialogActionChangeDialogState(int targetState);
    DialogActionChangeDialogState();
    void setReceiver(IStateReceiver *receiver);
    void serialize(std::ofstream *outFile) override;
    void setValue(int targetState);

private:
    int targetState;
    IStateReceiver *receiver;
};

class DialogActionAddQuest : public IDialogAction
{
public:
    void execute() override;
    DialogActionAddQuest(Quest *quest);
    DialogActionAddQuest();
    void serialize(std::ofstream *outFile) override;
    void setValue(Quest *quest);

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
    void setConditions(std::vector<IDialogCondition *> *conditions);
    void setActions(std::vector<IDialogAction *> *actions);
    std::vector<IDialogCondition *> *getConditions();
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
    void setDialogStates(std::vector<DialogState *> *states);
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
