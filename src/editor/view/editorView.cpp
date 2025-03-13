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

void inputEnter(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(GLFW_KEY_ENTER);
}

void inputEscape(SEngine::IEngineCallback *gc, int key)
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
void inputE(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('e');
}
void inputT(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput('t');
}

void EditorView::initLoadingScene()
{
    int windowWidth, windowHeight;
    GLFWwindow *window = engine->getWindow();
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    loadingScene = new SEngine::Scene();
    SEngine::Button *first = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    first->text = "Load map";
    first->callback = &inputEnter;
    SEngine::TextInput *second = new SEngine::TextInput(windowWidth / 2 - 130, windowHeight / 2 + 30, windowWidth / 2 + 130, windowHeight / 2 + 60);
    second->text = "/tests/level/level1";
    SEngine::Button *third = new SEngine::Button(windowWidth / 2 - 40, windowHeight / 2 + 200, windowWidth / 2 + 40, windowHeight / 2 + 230);
    third->text = "Exit";
    third->callback = &inputEscape;
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
    grid = new SEngine::SpriteGrid(windowWidth / 2 - 320, 80, windowWidth / 2 + 320, 720, texturePath, 0.25f);
    grid->setGrid(new std::vector<std::vector<SEngine::Sprite> *>());
    grid->setHighlightFocussedSprite(true);
    SEngine::Button *backButton = new SEngine::Button(windowWidth - 160, windowHeight / 2 + 200, windowWidth - 20, windowHeight / 2 + 230);
    backButton->text = "Back";
    backButton->callback = &inputEscape;
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
    tpButton->callback = &inputE;
    tpButton->setVisible(false);

    saveButton = new SEngine::Button(windowWidth - 160, 200, windowWidth - 20, 230);
    saveButton->text = "Save map";
    saveButton->callback = &inputS;

    editorScene->scene_elements = new std::vector<SEngine::Element *>(1, background);
    editorScene->scene_elements->push_back(grid);
    editorScene->scene_elements->push_back(addButton);
    editorScene->scene_elements->push_back(wallButton);
    editorScene->scene_elements->push_back(groundButton);
    editorScene->scene_elements->push_back(enemyButton);
    editorScene->scene_elements->push_back(tpButton);
    editorScene->scene_elements->push_back(saveButton);
    editorScene->scene_elements->push_back(backButton);
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
        saveButton->setVisible(true);
    }
    else if (state == 2)
    {
        wallButton->setVisible(true);
        groundButton->setVisible(true);
        enemyButton->setVisible(true);
        saveButton->setVisible(false);
    }
}

void EditorView::setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid)
{
    this->grid->setGrid(grid);
}
int EditorView::getFocussedSpriteX() { return grid->getFocussedSpriteX(); }
int EditorView::getFocussedSpriteY() { return grid->getFocussedSpriteY(); }