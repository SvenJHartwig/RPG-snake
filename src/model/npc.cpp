#include "npc.h"
#include "../services/gameModeService.h"
#include "../services/gameControllerService.h"
#include <typeinfo>

bool DialogConditionIsState::evaluate(int dialogState)
{
    return dialogState == stateToReach;
}

DialogConditionIsState::DialogConditionIsState(int stateToReach)
{
    this->stateToReach = stateToReach;
}

bool DialogConditionQuestFinished::evaluate(int dialogState)
{
    GameControllerService::get()->showQuests();
    bool exists;
    Quest *quest;
    std::tie(exists, quest) = GameModeService::get()->getQuest(questID);
    if (exists)
    {
        return quest->checkWinCondition();
    }
    return false;
}

DialogConditionQuestFinished::DialogConditionQuestFinished(std::string questID)
{
    this->questID = questID;
}

void DialogActionShowText::execute()
{
    GameControllerService::get()->setText(text);
}
DialogActionShowText::DialogActionShowText(std::string text)
{
    this->text = text;
}

void DialogActionChangeDialogState::execute()
{
    receiver->changeState(targetState);
}
DialogActionChangeDialogState::DialogActionChangeDialogState(int targetState)
{
    this->targetState = targetState;
}
void DialogActionChangeDialogState::setReceiver(IStateReceiver *receiver)
{
    this->receiver = receiver;
}
void DialogActionChangeDialogState::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&typeid(this)), sizeof(typeid(this)));
    outFile->write(reinterpret_cast<const char *>(&targetState), sizeof(int));
}

void DialogActionAddQuest::execute()
{
    GameModeService::get()->addQuest(quest);
    GameControllerService::get()->showQuests();
}
DialogActionAddQuest::DialogActionAddQuest(Quest *quest)
{
    this->quest = quest;
}
void DialogActionAddQuest::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&typeid(this)), sizeof(typeid(this)));
    outFile->write(reinterpret_cast<const char *>(&quest->getName()), sizeof(quest->getName()));
}

bool DialogState::evaluate(int dialogState)
{
    for (IDialogCondition *condition : *conditions)
    {
        if (!condition->evaluate(dialogState))
        {
            return false;
        }
    }
    return true;
}
void DialogState::execute()
{
    for (IDialogAction *action : *actions)
    {
        action->execute();
    }
}

DialogState::DialogState(std::vector<IDialogCondition *> *conditions,
                         std::vector<IDialogAction *> *actions)
{
    this->conditions = conditions;
    this->actions = actions;
}
std::vector<IDialogAction *> *DialogState::getActions()
{
    return actions;
}
void DialogState::serialize(std::ofstream *outFile)
{
    for (IDialogCondition *condition : *conditions)
    {
        condition->serialize(outFile);
    }
    for (IDialogAction *action : *actions)
    {
        action->serialize(outFile);
    }
}

void NPC_Dialog::changeState(int state)
{
    dialogState = state;
}

int NPC_Dialog::getState()
{
    return dialogState;
}
NPC_Dialog::NPC_Dialog(std::vector<DialogState *> *states)
{
    dialogState = 0;
    for (DialogState *state : *states)
    {
        for (IDialogAction *action : *state->getActions())
        {
            DialogActionChangeDialogState *changeStateAction = dynamic_cast<DialogActionChangeDialogState *>(action);
            if (changeStateAction)
            {
                changeStateAction->setReceiver(this);
            }
        }
    }
    this->states = states;
}
void NPC_Dialog::invoke()
{
    for (DialogState *state : *states)
    {
        if (state->evaluate(dialogState))
        {
            state->execute();
            return;
        }
    }
}
void NPC_Dialog::serialize(std::ofstream *outFile)
{
    for (DialogState *state : *states)
    {
        state->serialize(outFile);
    }
}

void NPC::snakeOnElement(IGridController *controller)
{
    if (stillOnElement)
    {
        return;
    }
    stillOnElement = true;
    dialog.get()->invoke();
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
    dialog->serialize(outFile);
}
void NPC::tick() {}
NPC::NPC(int pos_x, int pos_y)
{
    stillOnElement = false;
    quest = new Quest("NPC Quest", new WinCondition(WinConType::SCORE, 10));
    this->pos_x = pos_x;
    this->pos_y = pos_y;

    createSampleDialog();
}
NPC::~NPC() {}
void NPC::createSampleDialog()
{
    Quest *quest = new Quest("NPC Quest", new WinCondition(WinConType::SCORE, 10));

    DialogConditionIsState *conditionState0 = new DialogConditionIsState(0);
    DialogActionShowText *actionState0ShowText = new DialogActionShowText("Please get 10 points");
    DialogActionAddQuest *actionState0AddQuest = new DialogActionAddQuest(quest);
    DialogActionChangeDialogState *actionState0 = new DialogActionChangeDialogState(1);

    DialogConditionIsState *conditionState1 = new DialogConditionIsState(1);
    DialogActionShowText *actionState1ShowText = new DialogActionShowText("You have a quest");
    DialogActionChangeDialogState *actionState1 = new DialogActionChangeDialogState(2);
    DialogConditionQuestFinished *conditionQuestFinished = new DialogConditionQuestFinished(quest->getName());
    DialogActionShowText *actionState1ShowTextQuestFinished = new DialogActionShowText("Thanks");
    std::vector<DialogState *> *states = new std::vector<DialogState *>();

    std::vector<IDialogCondition *> *conditionsState0 = new std::vector<IDialogCondition *>(1, conditionState0);
    std::vector<IDialogAction *> *actionsState0 = new std::vector<IDialogAction *>(1, actionState0ShowText);
    actionsState0->push_back(actionState0AddQuest);
    actionsState0->push_back(actionState0);
    states->push_back(new DialogState(conditionsState0, actionsState0));

    std::vector<IDialogCondition *> *conditionsState1Quest = new std::vector<IDialogCondition *>(1, conditionState1);
    conditionsState1Quest->push_back(conditionQuestFinished);
    std::vector<IDialogAction *> *actionsState1Quest = new std::vector<IDialogAction *>(1, actionState1ShowTextQuestFinished);
    actionsState1Quest->push_back(actionState1);
    states->push_back(new DialogState(conditionsState1Quest, actionsState1Quest));

    std::vector<IDialogCondition *> *conditionsState1 = new std::vector<IDialogCondition *>(1, conditionState1);
    std::vector<IDialogAction *> *actionsState1 = new std::vector<IDialogAction *>(1, actionState1ShowText);
    states->push_back(new DialogState(conditionsState1, actionsState1));

    dialog = std::make_shared<NPC_Dialog>(states);
}
