#include "renderEngine.h"
#include <string>

using std::string;

void engine_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
    {
        return;
    }
    RenderEngine *engine = static_cast<RenderEngine *>(glfwGetWindowUserPointer(window));
    switch (key)
    {
    case GLFW_KEY_RIGHT:
        engine->getEngineCallback()->reactOnInput('d');
        break;
    case GLFW_KEY_LEFT:
        engine->getEngineCallback()->reactOnInput('a');
        break;
    case GLFW_KEY_UP:
        engine->getEngineCallback()->reactOnInput('w');
        break;
    case GLFW_KEY_DOWN:
        engine->getEngineCallback()->reactOnInput('s');
        break;
    case GLFW_KEY_P:
        engine->getEngineCallback()->reactOnInput('p');
        break;
    case GLFW_KEY_L:
        engine->getEngineCallback()->reactOnInput('l');
        break;
    case GLFW_KEY_O:
        engine->getEngineCallback()->reactOnInput('o');
        break;
    }
}

void engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (action != GLFW_PRESS)
    {
        return;
    }
    RenderEngine *engine = static_cast<RenderEngine *>(glfwGetWindowUserPointer(window));
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    for (int i = 0; i < engine->getCurrentScene()->scene_elements->size(); i++)
    {
        Element *currentSceneElement = engine->getCurrentScene()->scene_elements->at(i);
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        int xpostl = currentSceneElement->getPosXTopLeft();
        int ypostl = windowHeight - currentSceneElement->getPosYTopLeft();
        int xposbr = currentSceneElement->getPosXBottomRight();
        int yposbr = windowHeight - currentSceneElement->getPosYBottomRight();
        if (xpos > xpostl && xpos < xposbr &&
            ypos > ypostl && ypos < yposbr)
        {
            currentSceneElement->callback(engine->getEngineCallback());
        }
    }
}

void RenderEngine::renderingLoop()
{
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < currentScene->scene_elements->size(); i++)
        {
            currentScene->scene_elements->at(i)->render();
        }
        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    callback->setWindowClosed(true);
    glfwTerminate();
}

int RenderEngine::init()
{
    int error = 0;
    if (!glfwInit())
    {
        error = -1;
    }

    // Create a window
    window = glfwCreateWindow(1024, 768, "Snake", NULL, NULL);
    if (!window)
    {
        error = -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        error = -1;
    }

    // Initialize text renderer
    string path = RESOURCE_DIR;
    path.append("/fonts/WorkSans-Black.ttf");
    fd->init(path.c_str(), 10);

    // Initialize input callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, engine_key_callback);
    glfwSetMouseButtonCallback(window, engine_mouse_button_callback);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, 0, windowWidth, windowHeight);

    if (error != 0)
    {
        callback->setWindowClosed(true);
        glfwTerminate();
    }

    return 0;
}