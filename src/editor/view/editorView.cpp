#include "editorView.h"
#include <iostream>
#include "../../view/engine/renderEngine.h"
#include "../../view/engine/iEngineCallback.h"
#include "../../view/engine/elements/textInput.h"
#include "../../view/engine/elements/image.h"
#include <thread>

std::string EditorView::showOutput(std::string out)
{
    std::string input;
    std::cout << out;
    std::cin >> input;
    return input;
}
EditorView::EditorView() {}

void editorInitView(SEngine::IRenderEngine *engine, EditorView *view)
{
    engine->init();
    view->initLoadingScene();
    view->initEditorScene();
    view->setInitialized(true);
    engine->setEngineCallback(view->getCallback());
    engine->addScene(view->getLoadingScene());
    engine->renderingLoop();
}

int EditorView::init()
{
    delete (engine);
    engine = new SEngine::RenderEngine();
    const std::thread *initThread = new std::thread(editorInitView, engine, this);

    return 0;
}

void inputEnterEditor(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(GLFW_KEY_ENTER);
}

void inputEscapeEditor(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(GLFW_KEY_F25);
}

void inputAdd(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('a');
}
void inputW(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('w');
}
void inputG(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('g');
}
void inputS(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('s');
}
void inputD(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('d');
}
void inputE(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('e');
}
void inputT(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('t');
}
void inputN(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('n');
}
void inputC(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('c');
}
void inputB1(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(1);
}
void inputB2(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(2);
}
void inputB3(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(3);
}
void inputB4(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(4);
}
void inputB5(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(5);
}
void inputB6(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(6);
}

void EditorView::initLoadingScene()
{
    int windowWidth, windowHeight;
    GLFWwindow *window = engine->getWindow();
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    loadingScene = new SEngine::Scene();
    SEngine::Button *first = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    first->text = "Load map";
    first->callback = &inputEnterEditor;
    SEngine::TextInput *second = new SEngine::TextInput(windowWidth / 2 - 130, windowHeight / 2 + 30, windowWidth / 2 + 130, windowHeight / 2 + 60);
    second->text = "/tests/level/level1";
    SEngine::Button *third = new SEngine::Button(windowWidth / 2 - 40, windowHeight / 2 + 200, windowWidth / 2 + 40, windowHeight / 2 + 230);
    third->text = "Exit";
    third->callback = &inputEscapeEditor;
    loadingScene->scene_elements = new std::vector<SEngine::Element *>(1, first);
    loadingScene->scene_elements->push_back(second);
    loadingScene->scene_elements->push_back(third);
}

void EditorView::initEditorScene()
{
    int windowWidth, windowHeight;
    GLFWwindow *window = engine->getWindow();
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    editorScene = new SEngine::Scene();
    SEngine::Image *background = new SEngine::Image(windowWidth / 2 - 320, 80, windowWidth / 2 + 320, 720, ((std::string)RESOURCE_DIR).append("/textures/background.png").c_str(), SEngine::StretchMode::ORIGINAL);
    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    grid = new SEngine::SpriteGrid(windowWidth / 2 - 320, 80, windowWidth / 2 + 320, 720, texturePath, 0.125f);
    grid->setGrid(new std::vector<std::vector<SEngine::Sprite> *>());
    grid->setHighlightFocussedSprite(true);
    SEngine::Button *backButton = new SEngine::Button(windowWidth - 160, windowHeight / 2 + 200, windowWidth - 20, windowHeight / 2 + 230);
    backButton->text = "Back";
    backButton->callback = &inputEscapeEditor;
    SEngine::Button *addButton = new SEngine::Button(windowWidth - 160, 160, windowWidth - 20, 190);
    addButton->text = "Add Element";
    addButton->callback = &inputAdd;
    wallButton = new SEngine::Button(windowWidth - 160, 200, windowWidth - 20, 230);
    wallButton->text = "Wall";
    wallButton->callback = &inputW;
    wallButton->setVisible(false);
    groundButton = new SEngine::Button(windowWidth - 160, 240, windowWidth - 20, 270);
    groundButton->text = "Ground";
    groundButton->callback = &inputG;
    groundButton->setVisible(false);
    enemyButton = new SEngine::Button(windowWidth - 160, 280, windowWidth - 20, 310);
    enemyButton->text = "Enemy";
    enemyButton->callback = &inputE;
    enemyButton->setVisible(false);
    tpButton = new SEngine::Button(windowWidth - 160, 320, windowWidth - 20, 350);
    tpButton->text = "Teleporter";
    tpButton->callback = &inputT;
    tpButton->setVisible(false);
    npcButton = new SEngine::Button(windowWidth - 160, 360, windowWidth - 20, 390);
    npcButton->text = "NPC";
    npcButton->callback = &inputN;
    npcButton->setVisible(false);

    input1 = new SEngine::TextInput(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    input1->setVisible(false);
    input2 = new SEngine::TextInput(windowWidth / 2 - 80, windowHeight / 2 + 10, windowWidth / 2 + 80, windowHeight / 2 + 40);
    input2->setVisible(false);
    input3 = new SEngine::TextInput(windowWidth / 2 - 80, windowHeight / 2 + 50, windowWidth / 2 + 80, windowHeight / 2 + 80);
    input3->setVisible(false);

    saveButton = new SEngine::Button(windowWidth - 160, 200, windowWidth - 20, 230);
    saveButton->text = "Save map";
    saveButton->callback = &inputS;

    saveAsButton = new SEngine::Button(windowWidth - 160, 240, windowWidth - 20, 270);
    saveAsButton->text = "Save map as";
    saveAsButton->callback = &inputD;

    changeNPCDialogButton = new SEngine::Button(windowWidth - 160, 280, windowWidth - 20, 310);
    changeNPCDialogButton->text = "Change NPC dialog";
    changeNPCDialogButton->callback = &inputC;

    addDialogState = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    addDialogState->setVisible(false);
    addDialogState->text = "Add Dialog State";
    addDialogState->callback = &inputB1;
    addDialogConditionIsState = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    addDialogConditionIsState->setVisible(false);
    addDialogConditionIsState->text = "Add Dialog Condition is State";
    addDialogConditionIsState->callback = &inputB2;
    addDialogConditionQuestFinished = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 + 10, windowWidth / 2 + 80, windowHeight / 2 + 40);
    addDialogConditionQuestFinished->setVisible(false);
    addDialogConditionQuestFinished->text = "Add Dialog Condition quest finished";
    addDialogConditionQuestFinished->callback = &inputB3;
    addDialogActionShowText = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 + 50, windowWidth / 2 + 80, windowHeight / 2 + 80);
    addDialogActionShowText->setVisible(false);
    addDialogActionShowText->text = "Add Dialog Action show text";
    addDialogActionShowText->callback = &inputB4;
    addDialogActionChangeDialogState = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 + 90, windowWidth / 2 + 80, windowHeight / 2 + 120);
    addDialogActionChangeDialogState->setVisible(false);
    addDialogActionChangeDialogState->text = "Add Dialog Action change state";
    addDialogActionChangeDialogState->callback = &inputB5;
    addDialogActionAddQuest = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 + 130, windowWidth / 2 + 80, windowHeight / 2 + 160);
    addDialogActionAddQuest->setVisible(false);
    addDialogActionAddQuest->text = "Add Dialog Action Add Quest";
    addDialogActionAddQuest->callback = &inputB6;

    editorScene->scene_elements = new std::vector<SEngine::Element *>(1, background);
    editorScene->scene_elements->push_back(grid);
    editorScene->scene_elements->push_back(addButton);
    editorScene->scene_elements->push_back(wallButton);
    editorScene->scene_elements->push_back(groundButton);
    editorScene->scene_elements->push_back(enemyButton);
    editorScene->scene_elements->push_back(tpButton);
    editorScene->scene_elements->push_back(npcButton);
    editorScene->scene_elements->push_back(input1);
    editorScene->scene_elements->push_back(input2);
    editorScene->scene_elements->push_back(input3);
    editorScene->scene_elements->push_back(saveButton);
    editorScene->scene_elements->push_back(saveAsButton);
    editorScene->scene_elements->push_back(changeNPCDialogButton);
    editorScene->scene_elements->push_back(backButton);
    editorScene->scene_elements->push_back(addDialogState);
    editorScene->scene_elements->push_back(addDialogConditionIsState);
    editorScene->scene_elements->push_back(addDialogConditionQuestFinished);
    editorScene->scene_elements->push_back(addDialogActionShowText);
    editorScene->scene_elements->push_back(addDialogActionChangeDialogState);
    editorScene->scene_elements->push_back(addDialogActionAddQuest);
}

void EditorView::setCallback(SEngine::IEngineCallback *callback)
{
    this->callback = callback;
}
SEngine::IEngineCallback *EditorView::getCallback()
{
    return callback;
}
std::string EditorView::getText()
{
    return static_cast<SEngine::TextInput *>(loadingScene->scene_elements->at(1))->text;
}
void EditorView::setState(int state)
{
    if (state == 0)
    {
        engine->getScenes()->clear();
        engine->addScene(loadingScene);
    }
    else if (state == 1)
    {
        engine->getScenes()->clear();
        engine->addScene(editorScene);
        wallButton->setVisible(false);
        groundButton->setVisible(false);
        enemyButton->setVisible(false);
        tpButton->setVisible(false);
        npcButton->setVisible(false);
        saveButton->setVisible(true);
        saveAsButton->setVisible(true);
        input1->setVisible(false);
        input2->setVisible(false);
        input3->setVisible(false);
        changeNPCDialogButton->setVisible(true);
    }
    else if (state == 2)
    {
        wallButton->setVisible(true);
        groundButton->setVisible(true);
        enemyButton->setVisible(true);
        tpButton->setVisible(true);
        npcButton->setVisible(true);
        saveButton->setVisible(false);
        saveAsButton->setVisible(false);
        input1->setVisible(false);
        input2->setVisible(false);
        input3->setVisible(false);
        changeNPCDialogButton->setVisible(false);
    }
    else if (state == 3)
    {
        input1->setVisible(true);
        input2->setVisible(true);
        input3->setVisible(true);
    }
    else if (state == 4)
    {
        input1->setVisible(true);
    }
    else if (state == 5)
    {
        addDialogState->setVisible(true);
        addDialogConditionIsState->setVisible(false);
        addDialogConditionQuestFinished->setVisible(false);
        addDialogActionShowText->setVisible(false);
        addDialogActionChangeDialogState->setVisible(false);
        addDialogActionAddQuest->setVisible(false);
    }
    else if (state == 6)
    {
        addDialogState->setVisible(false);
        addDialogConditionIsState->setVisible(true);
        addDialogConditionQuestFinished->setVisible(true);
        addDialogActionShowText->setVisible(true);
        addDialogActionChangeDialogState->setVisible(true);
        addDialogActionAddQuest->setVisible(true);
    }
    else if (state == 7)
    {
        addDialogConditionIsState->setVisible(false);
        addDialogConditionQuestFinished->setVisible(false);
        addDialogActionShowText->setVisible(false);
        addDialogActionChangeDialogState->setVisible(false);
        addDialogActionAddQuest->setVisible(false);
        input1->setVisible(true);
    }
}

void EditorView::setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid)
{
    this->grid->setGrid(grid);
}
int EditorView::getFocussedSpriteX() { return grid->getFocussedSpriteX(); }
int EditorView::getFocussedSpriteY() { return grid->getFocussedSpriteY(); }
std::string EditorView::getTargetPath() { return input1->text; }
int EditorView::getTargetSpriteX()
{
    if (input2->text == "")
        return 0;
    return std::stoi(input2->text);
}
int EditorView::getTargetSpriteY()
{
    if (input3->text == "")
        return 0;
    return std::stoi(input3->text);
}