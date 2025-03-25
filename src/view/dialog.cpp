#include "dialog.h"
#include "./engine/elements/image.h"

void Dialog::show()
{
    engine->addScene(dialogScene);
}
void Dialog::close()
{
    engine->removeScene(dialogScene);
}
void Dialog::setText(std::string text) {}
Dialog::Dialog(SEngine::IRenderEngine *engine, std::string text)
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    dialogScene = new SEngine::Scene();
    SEngine::Image *backgroundImage = new SEngine::Image(windowWidth / 2 - 480, 600, windowWidth / 2 + 480, 720, ((std::string)RESOURCE_DIR).append("/textures/background.png").c_str(), SEngine::StretchMode::ORIGINAL);
    dialogScene->scene_elements->push_back(backgroundImage);
    this->engine = engine;
}
Dialog::~Dialog() {}