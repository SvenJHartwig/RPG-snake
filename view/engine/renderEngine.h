#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "elements/scene.h"
#include "TextRenderer/TextRenderer.h"
#include "iEngineCallback.h"
#include "iRenderEngine.h"

void engine_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

class RenderEngine : public IRenderEngine
{
private:
    font_data *fd = new font_data();
    GLFWwindow *window;
    Scene *currentScene;
    IEngineCallback *callback;
    unsigned int VBO, VAO, EBO;
    unsigned int shaderProgram;

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