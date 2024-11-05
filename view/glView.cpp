#include "glView.h"
#include "engine/elements/button.h"
#include "engine/elements/text.h"
#include "engine/elements/spriteGrid.h"
#include "engine/renderEngine.h"
#include <thread>

void GlView::renderingLoop()
{
    /*   // Main rendering loop
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
       glfwTerminate();*/
}

void gameControllerInitView(IRenderEngine *engine, GlView *view)
{
    engine->init();
    view->initMainMenu();
    view->initGameScene();
    engine->setCurrentScene(view->getMainMenu());
    engine->setEngineCallback(view->getGameController());
    view->setInitialized(true);
    engine->renderingLoop();
}

int GlView::init()
{
    engine = new RenderEngine();
    std::thread *initThread = new std::thread(gameControllerInitView, engine, this);

    return 0;
}

void inputP(IEngineCallback *gc)
{
    gc->reactOnInput('p');
}

void inputO(IEngineCallback *gc)
{
    gc->reactOnInput('o');
}

void inputL(IEngineCallback *gc)
{
    gc->reactOnInput('l');
}

void GlView::initGameScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    inGame = new Scene();
    Text *scoreText = new Text(0, windowHeight - 20, 40, windowHeight);
    scoreText->text = "Score: 0";
    scoreText->fd = engine->getFontData();
    inGame->scene_elements = new std::vector<Element *>(1, scoreText);
    SpriteGrid *spriteGrid = new SpriteGrid(20, windowHeight - 80, 200, 100);
    spriteGrid->setGrid(new vector<string>());
    inGame->scene_elements->push_back(spriteGrid);
}

void GlView::initMainMenu()
{
    mainMenu = new Scene();
    Button *first = new Button(340, 280, 400, 260);
    first->text = "Begin game";
    first->fd = engine->getFontData();
    first->callback = &inputP;
    Button *second = new Button(340, 260, 400, 240);
    second->text = "Load level";
    second->fd = engine->getFontData();
    second->callback = &inputO;
    Button *third = new Button(340, 220, 400, 200);
    third->text = "Exit";
    third->fd = engine->getFontData();
    third->callback = &inputL;
    mainMenu->scene_elements = new std::vector<Element *>(1, first);
    mainMenu->scene_elements->push_back(second);
    mainMenu->scene_elements->push_back(third);
}

void GlView::gameStateChanged(GameState game_state)
{
    if (game_state == IN_GAME)
    {
        engine->setCurrentScene(inGame);
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        engine->setCurrentScene(mainMenu);
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void GlView::setScore(int count)
{
    ((Text *)inGame->scene_elements->at(0))->text = "Score: " + std::to_string(gameController->getScore());
}

void GlView::setGrid(vector<string> *grid)
{
    ((SpriteGrid *)inGame->scene_elements->at(1))->setGrid(grid);
}