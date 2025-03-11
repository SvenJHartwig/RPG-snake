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
        if (state == 0)
        {
            exit = true;
        }
        else if (state == 1)
        {
            path = RESOURCE_DIR;
            state = 0;
            view->setState(state);
        }
        else if (state == 2)
        {
            state = 1;
            view->setState(state);
        }
    }
    else if (key == GLFW_KEY_ENTER)
    {
        input = view->getText();
        path.append(input);
        grid = new Grid();
        loadLevelFromBinaryFile(path.c_str(), grid);
        state = 1;
        view->setGrid(getSpriteVector());
        view->setState(state);
    }
    if (state == 1)
    {
        if (key == 'a')
        {
            state = 2;
            view->setState(state);
        }
    }
}
void EditorController::setWindowClosed(bool closed)
{
    exit = closed;
}
std::vector<std::vector<SEngine::Sprite> *> *EditorController::getSpriteVector()
{
    // TODO: Unify with GridController::getSpriteVector into a new SpriteVectorProvider
    using SEngine::Sprite;
    std::vector<std::vector<Sprite> *> *result = new std::vector<std::vector<Sprite> *>();
    // Level grid
    for (int yCoord = 0; yCoord < grid->getLevel()->size(); yCoord++)
    {
        std::vector<Sprite> *inner = new std::vector<Sprite>(grid->getLevel()->at(yCoord)->size());
        result->push_back(inner);
        for (int xCoord = 0; xCoord < grid->getLevel()->at(yCoord)->size(); xCoord++)
        {
            Sprite tempSprite = Sprite();
            if (dynamic_cast<Wall *>(grid->getLevel()->at(yCoord)->at(xCoord)))
            {
                tempSprite.texBaseX = 0.0f;
                tempSprite.texBaseY = 0.0f;
            }
            else if (dynamic_cast<Teleporter *>(grid->getLevel()->at(yCoord)->at(xCoord)))
            {
                tempSprite.texBaseX = 0.75f;
                tempSprite.texBaseY = 0.75f;
            }
            else
            {
                tempSprite.texBaseX = 0.25f;
                tempSprite.texBaseY = 0.0f;
            }
            result->at(yCoord)->at(xCoord) = tempSprite;
        }
    }
    for (Mob *mob : *grid->getMobs())
    {
        Sprite temp = result->at(mob->getPosY())->at(mob->getPosX());
        temp.texBaseX = 0.5f;
        temp.texBaseY = 0.75f;
        result->at(mob->getPosY())->at(mob->getPosX()) = temp;
    }
    return result;
}