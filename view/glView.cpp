#include "glView.h"
#include <GLFW/glfw3.h>

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

    // Main game loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        glfwPollEvents();

        // Rendering code goes here

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glfwTerminate();

    return 0;
}

void GlView::showGrid(char **grid, int grid_size_y)
{
}