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
    view->setInitialized(true);
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

void inputP(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(GLFW_KEY_P);
}

void inputL(SEngine::IEngineCallback *gc, int key)
{
    gc->reactOnInput(GLFW_KEY_L);
}

void EditorView::initLoadingScene()
{
    int windowWidth, windowHeight;
    GLFWwindow *window = engine->getWindow();
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    loadingScene = new SEngine::Scene();
    SEngine::Button *first = new SEngine::Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    first->text = "Load map";
    first->callback = &inputP;
    SEngine::TextInput *second = new SEngine::TextInput(windowWidth / 2 - 80, windowHeight / 2 + 30, windowWidth / 2 + 80, windowHeight / 2 + 60);
    SEngine::Button *third = new SEngine::Button(windowWidth / 2 - 40, windowHeight / 2 + 200, windowWidth / 2 + 40, windowHeight / 2 + 230);
    third->text = "Exit";
    third->callback = &inputL;
    loadingScene->scene_elements = new std::vector<SEngine::Element *>(1, first);
    loadingScene->scene_elements->push_back(second);
    loadingScene->scene_elements->push_back(third);
}