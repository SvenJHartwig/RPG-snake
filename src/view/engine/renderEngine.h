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
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

    // Main class of the rendering engine. To use, create an instance of this class and then call the init method on that object.
    class RenderEngine : public IRenderEngine
    {
    private:
        GLFWwindow *window;
        Scene *currentScene;
        IEngineCallback *callback;
        unsigned int VBO, VAO, EBO;
        TextRenderer *textRenderer;
        Shader *textureShader;
        Shader *colorShader;

    public:
        IEngineCallback *getEngineCallback() override { return callback; }
        // Set the engine callback object. That objects reactOnInput method is called every time the user presses a button on the OpenGL window.
        void setEngineCallback(IEngineCallback *callback) override { this->callback = callback; }
        // Set the Scene to render in the RenderEngine.
        void setCurrentScene(Scene *currentScene) override { this->currentScene = currentScene; }
        // Return the scene that is currently rendered by this RenderEngine.
        Scene *getCurrentScene() override { return currentScene; }
        // Return the GLFWwindow.
        GLFWwindow *getWindow() override { return window; }
        // Start the rendering loop. Call only once and only in the same thread as init.
        void renderingLoop() override;
        // Initialize the RenderEngine. Call once in the beginning.
        int init() override;
    };
}