#include "glView.h"
#include "elements/button.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
    {
        return;
    }
    GlView *view = static_cast<GlView *>(glfwGetWindowUserPointer(window));
    switch (key)
    {
    case GLFW_KEY_RIGHT:
        view->getGameController()->reactOnInput('d');
        break;
    case GLFW_KEY_LEFT:
        view->getGameController()->reactOnInput('a');
        break;
    case GLFW_KEY_UP:
        view->getGameController()->reactOnInput('w');
        break;
    case GLFW_KEY_DOWN:
        view->getGameController()->reactOnInput('s');
        break;
    case GLFW_KEY_P:
        view->getGameController()->reactOnInput('p');
        break;
    case GLFW_KEY_L:
        view->getGameController()->reactOnInput('l');
        break;
    case GLFW_KEY_O:
        view->getGameController()->reactOnInput('o');
        break;
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (action != GLFW_PRESS)
    {
        return;
    }
    GlView *view = static_cast<GlView *>(glfwGetWindowUserPointer(window));
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    for (int i = 0; i < view->getCurrentScene()->scene_elements->size(); i++)
    {
        Element *currentSceneElement = view->getCurrentScene()->scene_elements->at(i);
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
            currentSceneElement->callback(view->getGameController());
        }
    }
}

void GlView::renderingLoop()
{
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        Grid grid;
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
            grid = gameController->getGrid();
            showGrid(grid.getGrid(), grid.getGridSizeX(), grid.getGridSizeY());
            break;
        case GAME_OVER:
            showUI(gameController->getScore());
            grid = gameController->getGrid();
            showGrid(grid.getGrid(), grid.getGridSizeX(), grid.getGridSizeY());
            glColor3f(0.9f, 0.9f, 0.9f);
            print(*fd, 400, 300, "GAME OVER");
            print(*fd, 400, 270, "PRESS P TO RETURN TO MAIN MENU");
            break;
        }

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

    // Initialize input callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (error != 0)
    {
        gameController->setWindowClosed(true);
        glfwTerminate();
    }

    initMainMenu();

    currentScene = mainMenu;

    return 0;
}

void inputP(IGameController *gc)
{
    gc->reactOnInput('p');
}

void inputO(IGameController *gc)
{
    gc->reactOnInput('o');
}

void inputL(IGameController *gc)
{
    gc->reactOnInput('l');
}

void GlView::initMainMenu()
{
    // TODO Move this out of here
    mainMenu = new Scene();
    Button *first = new Button(340, 280, 400, 260);
    first->text = "Begin game";
    first->fd = fd;
    first->callback = &inputP;
    Button *second = new Button(340, 260, 400, 240);
    second->text = "Load level";
    second->fd = fd;
    second->callback = &inputO;
    Button *third = new Button(340, 220, 400, 200);
    third->text = "Exit";
    third->fd = fd;
    third->callback = &inputL;
    mainMenu->scene_elements = new std::vector<Element *>(2, first);
    mainMenu->scene_elements->push_back(second);
    mainMenu->scene_elements->push_back(third);
}

void GlView::showUI(int eatenFoods)
{
    glColor3f(0.9f, 0.9f, 0.9f);
    print(*fd, 0, 0, "Score: " + std::to_string(eatenFoods));
}

void GlView::showGrid(vector<string> *grid, int grid_size_x, int grid_size_y)
{
    for (int i = 0; i < grid_size_y; i++)
    {
        for (int j = 0; j < grid_size_x; j++)
        {
            glBegin(GL_QUADS);
            switch (grid->at(i)[j])
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