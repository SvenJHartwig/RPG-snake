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
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            gameController->reactOnInput('d');
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            gameController->reactOnInput('a');
        }
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            gameController->reactOnInput('w');
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            gameController->reactOnInput('s');
        }

        Grid grid = gameController->getGrid();
        showGrid(grid.getGrid(), grid.getGridSizeX(), grid.getGridSizeY());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    gameController->setWindowClosed(true);

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

void GlView::showGrid(char **grid, int grid_size_x, int grid_size_y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < grid_size_y; i++)
    {
        for (int j = 0; j < grid_size_x; j++)
        {
            glBegin(GL_TRIANGLE_FAN);
            switch (grid[i][j])
            {
            case 'W':
                glColor3f(0.9f, 0.9f, 0.9f);
                break;
            case 'H':
                glColor3f(0.9f, 0.2f, 0.2f);
                break;
            case 'B':
                glColor3f(0.8f, 0.2f, 0.2f);
                break;
            case 'F':
                glColor3f(0.2f, 0.9f, 0.2f);
                break;

            default:
                glColor3f(0.0f, 0.0f, 0.0f);
                break;
            }
            glVertex2f(-0.9f + j * 0.08, 0.9f - i * 0.08);
            glVertex2f(-0.8f + j * 0.08, 0.9f - i * 0.08);
            glVertex2f(-0.8f + j * 0.08, 0.8f - i * 0.08);
            glVertex2f(-0.9f + j * 0.08, 0.8f - i * 0.08);
            glEnd();
        }
    }
}