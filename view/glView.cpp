#include "glView.h"
#include "engine/elements/button.h"
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

void gameControllerInitView(RenderEngine *engine, GlView *view)
{
    engine->init();
    view->initMainMenu();
    engine->setCurrentScene(view->getMainMenu());
    engine->setEngineCallback(view->getGameController());
    engine->renderingLoop();
}

int GlView::init()
{
    engine = new RenderEngine();
    new std::thread(gameControllerInitView, engine, this);

    // initMainMenu();
    // engine->setCurrentScene(mainMenu);
    // engine->setEngineCallback(gameController);

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
    inGame = new Scene();
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
    mainMenu->scene_elements = new std::vector<Element *>(2, first);
    mainMenu->scene_elements->push_back(second);
    mainMenu->scene_elements->push_back(third);
}

void GlView::showUI(int eatenFoods)
{
    // glColor3f(0.9f, 0.9f, 0.9f);
    // print(*fd, 0, 0, "Score: " + std::to_string(eatenFoods));
}

void GlView::showGrid(vector<string> *grid, int grid_size_x, int grid_size_y)
{
    /*  for (int i = 0; i < grid_size_y; i++)
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
      }*/
}

void GlView::gameStateChanged(GameState game_state)
{
    if (game_state == IN_GAME)
    {
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}