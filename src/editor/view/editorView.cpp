#include "editorView.h"
#include <iostream>
#include "../../view/engine/renderEngine.h"
#include "../../view/engine/iEngineCallback.h"
#include "../../view/engine/elements/button.h"
#include "../../view/engine/elements/textInput.h"
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

void EditorView::initLoadingScene()
{
    int windowWidth, windowHeight;
    GLFWwindow *window = engine->getWindow();
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    loadingScene = new SEngine::Scene();
    SEngine::Button *first = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    first->text = "Load map";
    first->callback = &inputEnter;
    SEngine::TextInput *second = new SEngine::TextInput(windowWidth / 2 - 80, windowHeight / 2 + 30, windowWidth / 2 + 80, windowHeight / 2 + 60);
    second->text = "Test";
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
    SEngine::Button *first = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    first->text = "Test";
    first->callback = &inputEnter;
    SEngine::TextInput *second = new SEngine::TextInput(windowWidth / 2 - 80, windowHeight / 2 + 30, windowWidth / 2 + 80, windowHeight / 2 + 60);
    second->text = "Test";
    SEngine::Button *third = new SEngine::Button(windowWidth / 2 - 40, windowHeight / 2 + 200, windowWidth / 2 + 40, windowHeight / 2 + 230);
    third->text = "Exit";
    third->callback = &inputEscape;
    editorScene->scene_elements = new std::vector<SEngine::Element *>(1, first);
    editorScene->scene_elements->push_back(second);
    editorScene->scene_elements->push_back(third);
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
    }
}