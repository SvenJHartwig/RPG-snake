#pragma once
#include "elements/scene.h"
#include "iEngineCallback.h"
#include "iRenderEngine.h"
#include "shaders/shader.h"
#include "TextRenderer/TextRenderer.h"
#include <string>

namespace SEngine
{
    void engine_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    class RenderEngine : public IRenderEngine
    {
    private:
        GLFWwindow *window;
        Scene *currentScene;
        IEngineCallback *callback;
        unsigned int VBO, VAO, EBO;
        TextRenderer *textRenderer;
        Shader *colorShader;

    public:
        IEngineCallback *getEngineCallback() { return callback; }
        void setEngineCallback(IEngineCallback *callback) { this->callback = callback; }
        Scene *getCurrentScene() { return currentScene; }
        GLFWwindow *getWindow() { return window; }
        void setCurrentScene(Scene *currentScene) { this->currentScene = currentScene; }
        void renderingLoop();
        int init();
    };
}