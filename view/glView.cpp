#include "glView.h"

GLuint CreateTextureFromBitmap(FT_Bitmap *bitmap)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Upload the bitmap to the GPU (assuming it's grayscale)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap->width, bitmap->rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap->buffer);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->buffer);
    //  Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

void GlView::setGameController(IGameController *gc)
{
    this->gameController = gc;
}

void GlView::renderingLoop()
{
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        handleInput();

        glClear(GL_COLOR_BUFFER_BIT);
        showUI(gameController->getScore());
        Grid grid = gameController->getGrid();
        showGrid(grid.getGrid(), grid.getGridSizeX(), grid.getGridSizeY());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    gameController->setWindowClosed(true);
    glfwTerminate();
}

int GlView::init()
{
    int error = 0;
    if (!glfwInit())
    {
        error = -1;
    }

    // Create a window
    window = glfwCreateWindow(800, 600, "Snake", NULL, NULL);
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
    fd = new font_data();
    fd->init("../resources/fonts/WorkSans-Black.ttf", 10);

    if (error != 0)
    {
        gameController->setWindowClosed(true);
        glfwTerminate();
    }

    return 0;
}

void GlView::showUI(int eatenFoods)
{
    print(*fd, 0, 0, "Score: " + std::to_string(eatenFoods));
}

void GlView::showGrid(char **grid, int grid_size_x, int grid_size_y)
{
    for (int i = 0; i < grid_size_y; i++)
    {
        for (int j = 0; j < grid_size_x; j++)
        {
            glBegin(GL_QUADS);
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
            case 'S':
                glColor3f(0.1f, 0.1f, 0.9f);
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

void GlView::showMainMenu()
{

    glClear(GL_COLOR_BUFFER_BIT);
    print(*fd, 320, 240, "Begin game");
    print(*fd, 300, 240, "Exit");
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window) && gameController->getGameState() == MAIN_MENU)
    {
        handleInput();
    }
}

void GlView::handleInput()
{
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
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        gameController->reactOnInput('p');
    }
}