#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "elements/scene.h"
#include "../../TextRenderer/TextRenderer.h"
#include "iEngineCallback.h"

class RenderEngine
{
private:
    font_data *fd = new font_data();
    GLFWwindow *window;
    Scene *currentScene;
    IEngineCallback *callback;

public:
    IEngineCallback *getEngineCallback() { return callback; }
    void setEngineCallback(IEngineCallback *callback) { this->callback = callback; }
    Scene *getCurrentScene() { return currentScene; }
    GLFWwindow *getWindow() { return window; }
    void setCurrentScene(Scene *currentScene) { this->currentScene = currentScene; }
    void renderingLoop();
    int init();
    font_data *getFontData() { return fd; }
};