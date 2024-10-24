#include "glView.h"
#include "elements/button.h"

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
        switch (gameController->getGameState())
        {
        case MAIN_MENU:
            for (int i = 0; i < currentScene->scene_elements->size(); i++)
            {
                currentScene->scene_elements->at(i)->render();
            }
            break;
        case IN_GAME:
            showUI(gameController->getScore());
            Grid grid = gameController->getGrid();
            showGrid(grid.getGrid(), grid.getGridSizeX(), grid.getGridSizeY());
            break;
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    gameController->setWindowClosed(true);
    glfwTerminate();
}

void inputP(IGameController *gc)
{
    gc->reactOnInput('p');
}

void inputL(IGameController *gc)
{
    gc->reactOnInput('l');
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

    // TODO Move this out of here
    currentScene = new Scene();
    Button *first = new Button(340, 280, 400, 260);
    first->text = "Begin game";
    first->fd = fd;
    first->callback = &inputP;
    Button *second = new Button(340, 220, 400, 200);
    second->text = "Exit";
    second->fd = fd;
    second->callback = &inputL;
    currentScene->scene_elements = new std::vector<Element *>(2, first);
    currentScene->scene_elements->push_back(second);

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

void GlView::handleInput()
{
    glfwPollEvents();
    // Handling of key input
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
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        gameController->reactOnInput('l');
    }

    // Handling of mouse input
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        for (int i = 0; i < currentScene->scene_elements->size(); i++)
        {
            Element *currentSceneElement = currentScene->scene_elements->at(i);
            int windowWidth, windowHeight;
            glfwGetWindowSize(window, &windowWidth, &windowHeight);
            int elementHeight = currentSceneElement->getPosYTopLeft() - currentSceneElement->getPosYBottomRight();
            int xpostl = currentSceneElement->getPosXTopLeft();
            int ypostl = windowHeight - currentSceneElement->getPosYTopLeft() - elementHeight;
            int xposbr = currentSceneElement->getPosXBottomRight();
            int yposbr = windowHeight - currentSceneElement->getPosYBottomRight() - elementHeight;
            if (xpos > xpostl && xpos < xposbr &&
                ypos > ypostl && ypos < yposbr)
            {
                currentSceneElement->callback(gameController);
            }
        }
    }
}

void GlView::gameStateChanged(GameState game_state)
{
    if (game_state == IN_GAME)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void GlView::setCurrentScene(Scene *current_scene)
{
    this->currentScene = current_scene;
}