#include "editorController.h"

EditorController::EditorController(IEditorView *view)
{
    this->view = view;
    this->view->setCallback(this);
}
EditorController::~EditorController() {}
void EditorController::mainLoop()
{
    view->init();
    while (!exit)
    {
        mainLoopIteration();
    }
}
void EditorController::mainLoopIteration()
{
    if (state == 0)
    {
        /* input = view->showOutput("Choose option:\n1 - Load map\n2 - Exit\n");
         if (input.compare("1") == 0)
         {
             input = view->showOutput("Choose resource to open:\n");
             path.append(input);
             grid = new Grid();
             loadLevelFromBinaryFile(path.c_str(), grid);
             state = 1;
         }
         else if (input.compare("2") == 0)
         {
             exit = true;
         }*/
    }
    else if (state == 1)
    {
        /*  input = view->showOutput("Loaded: " + path + "\nChoose option:\n1 - Save map\n2 - Save map as\n3 - Add element\n4 - Back\n");
          if (input.compare("1") == 0)
          {
              saveGridAsBinaryFile(path, grid);
          }
          if (input.compare("2") == 0)
          {
              input = view->showOutput("File name:\n");
              path = RESOURCE_DIR;
              path.append(input);
              saveGridAsBinaryFile(path, grid);
          }
          if (input.compare("3") == 0)
          {
              input = view->showOutput("Position X:\n");
              x = std::stoi(input);
              input = view->showOutput("Position Y:\n");
              y = std::stoi(input);
              state = 2;
          }
          else if (input.compare("4") == 0)
          {
              path = RESOURCE_DIR;
              state = 0;
          }*/
    }
    else if (state == 2)
    {
        /*  input = view->showOutput("Choose option:\n1 - Wall\n2 - Ground\n3 - Enemy\n4 - Teleporter\n5 - Back:\n");
          if (input.compare("1") == 0)
          {
              grid->getLevel()->at(y)->at(x) = new Wall(x, y);
          }
          if (input.compare("2") == 0)
          {
              grid->getLevel()->at(y)->at(x) = new Ground(x, y);
          }
          if (input.compare("3") == 0)
          {
              grid->getLevel()->at(y)->at(x) = new Enemy(x, y);
          }
          if (input.compare("4") == 0)
          {
              input = view->showOutput("File name:\n");
              std::string mapPath = input;
              input = view->showOutput("Target Position X:\n");
              int targetX = std::stoi(input);
              input = view->showOutput("Target Position Y:\n");
              int targetY = std::stoi(input);
              grid->getLevel()->at(y)->at(x) = new Teleporter(x, y, mapPath, targetX, targetY);
          }
          else if (input.compare("5") == 0)
          {
              state = 1;
          }*/
    }
}

void EditorController::reactOnInput(int key)
{
    if (key == GLFW_KEY_F25)
    {
        exit = true;
    }
    else if (key == GLFW_KEY_ENTER)
    {
        input = view->getText();
        path.append(input);
        grid = new Grid();
        loadLevelFromBinaryFile(path.c_str(), grid);
        state = 1;
        view->setState(state);
    }
}
void EditorController::setWindowClosed(bool closed)
{
    exit = closed;
}