#include "glView.h"

void GlView::setGameController(IGameController *gc)
{
    this->gameController = gc;
}

void GlView::renderingLoop(GLFWwindow *window)
{
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
        }

        // Rendering code goes here

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glEnd();

        // TODO send input to gameController, retrieve via showGrid

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glfwTerminate();
}

int GlView::init()
{

    if (!glfwInit())
    {
        return -1;
    }

    // Create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // TODO Launch rendering in other thread
    renderingLoop(window);

    return 0;
}

void GlView::showGrid(char **grid, int grid_size_y)
{
}