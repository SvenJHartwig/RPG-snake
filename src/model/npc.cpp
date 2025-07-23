#include "npc.h"
#include "../services/gameModeService.h"
#include "../services/gameControllerService.h"
#include <typeinfo>
#include "../commonFunctions.h"

bool DialogConditionIsState::evaluate(int dialogState)
{
    return dialogState == stateToReach;
}

DialogConditionIsState::DialogConditionIsState(int stateToReach)
{
    this->stateToReach = stateToReach;
}
DialogConditionIsState::DialogConditionIsState() {}
void DialogConditionIsState::serialize(std::ofstream *outFile)
{
    serializeString(outFile, "DialogConditionIsState");
    outFile->write(reinterpret_cast<const char *>(&stateToReach), sizeof(int));
}
void DialogConditionIsState::setValue(int stateToReach)
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
DialogConditionQuestFinished::DialogConditionQuestFinished() {}
void DialogConditionQuestFinished::serialize(std::ofstream *outFile)
{
    serializeString(outFile, "DialogConditionQuestFinished");
    serializeString(outFile, questID);
}
void DialogConditionQuestFinished::setValue(std::string questID)
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
DialogActionShowText::DialogActionShowText() {}
void DialogActionShowText::setValue(std::string text)
{
    this->text = text;
}
void DialogActionShowText::serialize(std::ofstream *outFile)
{
    serializeString(outFile, "DialogActionShowText");
    serializeString(outFile, text);
}

void DialogActionChangeDialogState::execute()
{
    receiver->changeState(targetState);
}
DialogActionChangeDialogState::DialogActionChangeDialogState(int targetState)
{
    this->targetState = targetState;
}
DialogActionChangeDialogState::DialogActionChangeDialogState() {}
void DialogActionChangeDialogState::setReceiver(IStateReceiver *receiver)
{
    this->receiver = receiver;
}
void DialogActionChangeDialogState::serialize(std::ofstream *outFile)
{
    serializeString(outFile, "DialogActionChangeDialogState");
    outFile->write(reinterpret_cast<const char *>(&targetState), sizeof(int));
}
void DialogActionChangeDialogState::setValue(int targetState)
{
    this->targetState = targetState;
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
DialogActionAddQuest::DialogActionAddQuest() {}
void DialogActionAddQuest::serialize(std::ofstream *outFile)
{
    serializeString(outFile, "DialogActionAddQuest");
    serializeString(outFile, quest->getName());
}
void DialogActionAddQuest::setValue(Quest *quest)
{
    this->quest = quest;
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
DialogState::DialogState() {}
void DialogState::setConditions(std::vector<IDialogCondition *> *conditions)
{
    this->conditions = conditions;
}
void DialogState::setActions(std::vector<IDialogAction *> *actions)
{
    this->actions = actions;
}
std::vector<IDialogAction *> *DialogState::getActions()
{
    return actions;
}
void DialogState::serialize(std::ofstream *outFile)
{
    serializeString(outFile, "DialogState");
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
NPC_Dialog::NPC_Dialog()
{
    dialogState = 0;
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
void NPC_Dialog::setDialogStates(std::vector<DialogState *> *states)
{
    this->states = states;
}
std::vector<DialogState *> *NPC_Dialog::getStates()
{
    return states;
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
    serializeString(outFile, "DialogFinish");
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
void NPC::setDialog(NPC_Dialog *dialog)
{
    this->dialog = std::make_shared<NPC_Dialog>(dialog->getStates());
}
void NPC::loadDialogFromFile(std::ifstream *inFile)
{
    size_t strLength;
    std::string dialogType;
    inFile->read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    dialogType.resize(strLength);
    inFile->read(&dialogType[0], strLength);
    if (dialogType.compare("DialogState") != 0)
    {
        return;
    }
    std::vector<DialogState *> *states = new std::vector<DialogState *>();
    std::vector<IDialogCondition *> *conditions = new std::vector<IDialogCondition *>();
    std::vector<IDialogAction *> *actions = new std::vector<IDialogAction *>();
    while (dialogType.compare("DialogFinish") != 0)
    {
        inFile->read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
        dialogType.resize(strLength);
        inFile->read(&dialogType[0], strLength);
        if (dialogType.compare("DialogState") == 0)
        {
            states->push_back(new DialogState(conditions, actions));
            conditions = new std::vector<IDialogCondition *>();
            actions = new std::vector<IDialogAction *>();
        }
        if (dialogType.compare("DialogConditionIsState") == 0)
        {
            int state = 0;
            inFile->read(reinterpret_cast<char *>(&state), sizeof(state));
            DialogConditionIsState *conditionState = new DialogConditionIsState(state);
            conditions->push_back(conditionState);
        }
        if (dialogType.compare("DialogConditionQuestFinished") == 0)
        {
            inFile->read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
            dialogType.resize(strLength);
            inFile->read(&dialogType[0], strLength);
            DialogConditionQuestFinished *conditionQuest = new DialogConditionQuestFinished(dialogType);
            conditions->push_back(conditionQuest);
        }
        if (dialogType.compare("DialogActionShowText") == 0)
        {
            inFile->read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
            dialogType.resize(strLength);
            inFile->read(&dialogType[0], strLength);
            DialogActionShowText *actionText = new DialogActionShowText(dialogType);
            actions->push_back(actionText);
        }
        if (dialogType.compare("DialogActionChangeDialogState") == 0)
        {
            int state = 0;
            inFile->read(reinterpret_cast<char *>(&state), sizeof(state));
            DialogActionChangeDialogState *actionState = new DialogActionChangeDialogState(state);
            actions->push_back(actionState);
        }
        if (dialogType.compare("DialogActionAddQuest") == 0)
        {
            Quest *quest = new Quest("NPC Quest", new WinCondition(WinConType::SCORE, 10));
            inFile->read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
            dialogType.resize(strLength);
            inFile->read(&dialogType[0], strLength);
            DialogActionAddQuest *actionQuest = new DialogActionAddQuest(quest);
            actions->push_back(actionQuest);
        }
    }
    dialog = std::make_shared<NPC_Dialog>(states);
}
