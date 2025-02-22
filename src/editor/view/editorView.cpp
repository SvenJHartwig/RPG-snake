#include "editorView.h"
#include <iostream>
#include "../../view/engine/renderEngine.h"
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
    view->setInitialized(true);
    engine->renderingLoop();
}

int EditorView::init()
{
    delete (engine);
    engine = new SEngine::RenderEngine();
    const std::thread *initThread = new std::thread(editorInitView, engine, this);

    return 0;
}