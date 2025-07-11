#include "editorController.h"
#include "../../model/npc.h"
#include "../../controller/spriteController.h"

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
        usleep(100000);
    }
}
void EditorController::reactOnKeyReleased(int input) {}

void EditorController::reactOnInput(int key)
{

    if (state == 0)
    {
        handleInputForState0(key);
    }
    else if (state == 1)
    {
        handleInputForState1(key);
    }
    else if (state == 2)
    {
        handleInputForState2(key);
    }
    else if (state == 3)
    {
        handleInputForState3(key);
    }
    else if (state == 4)
    {
        handleInputForState4(key);
    }
    else if (state == 5)
    {
        handleInputForState5(key);
    }
    else if (state == 6)
    {
        handleInputForState6(key);
    }
    else if (state == 7)
    {
        handleInputForState7(key);
    }
}
void EditorController::handleInputForState0(int key)
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
        view->setGrid(SpriteController::getSpriteVector(grid, nullptr, nullptr));
        view->setState(state);
    }
}
void EditorController::handleInputForState1(int key)
{
    if (key == GLFW_KEY_F25)
    {
        path = RESOURCE_DIR;
        state = 0;
        view->setState(state);
    }
    else if (key == 'a')
    {
        state = 2;
        view->setState(state);
    }
    else if (key == 's')
    {
        saveGridAsBinaryFile(path, grid);
    }
    else if (key == 'd')
    {
        state = 4;
        view->setState(state);
    }
    else if (key == 'c')
    {
        state = 5;
        view->setState(state);
    }
}
void EditorController::handleInputForState2(int key)
{
    if (key == GLFW_KEY_F25)
    {
        state = 1;
        view->setState(state);
    }
    int focussedX = view->getFocussedSpriteX();
    int focussedY = view->getFocussedSpriteY();
    if (key == 'w')
    {
        eraseMobAt(focussedX, focussedY);
        grid->getLevel()->at(focussedY)->at(focussedX) = new Wall(focussedX, focussedY);
        view->setGrid(SpriteController::getSpriteVector(grid, nullptr, nullptr));
    }
    else if (key == 'g')
    {
        eraseMobAt(focussedX, focussedY);
        grid->getLevel()->at(focussedY)->at(focussedX) = new Ground(focussedX, focussedY);
        view->setGrid(SpriteController::getSpriteVector(grid, nullptr, nullptr));
    }
    else if (key == 'e')
    {
        eraseMobAt(focussedX, focussedY);
        grid->getLevel()->at(focussedY)->at(focussedX) = new Enemy(focussedX, focussedY);
        grid->getMobs()->push_back(new Enemy(focussedX, focussedY));
        view->setGrid(SpriteController::getSpriteVector(grid, nullptr, nullptr));
    }
    else if (key == 'n')
    {
        eraseMobAt(focussedX, focussedY);
        grid->getLevel()->at(focussedY)->at(focussedX) = new NPC(focussedX, focussedY);
        grid->getMobs()->push_back(new NPC(focussedX, focussedY));
        view->setGrid(SpriteController::getSpriteVector(grid, nullptr, nullptr));
    }
    else if (key == 't')
    {
        state = 3;
        view->setState(state);
    }
}
void EditorController::handleInputForState3(int key)
{
    if (key == GLFW_KEY_F25)
    {
        state = 2;
        view->setState(state);
    }
    if (key == GLFW_KEY_ENTER)
    {
        int focussedX = view->getFocussedSpriteX();
        int focussedY = view->getFocussedSpriteY();
        std::string targetPath = static_cast<std::string>(RESOURCE_DIR).append(view->getTargetPath());
        int targetX = view->getTargetSpriteX();
        int targetY = view->getTargetSpriteY();
        grid->getLevel()->at(focussedY)->at(focussedX) = new Teleporter(focussedX, focussedY, targetPath, targetX, targetY);
        view->setGrid(SpriteController::getSpriteVector(grid, nullptr, nullptr));
        state = 2;
        view->setState(state);
    }
}
void EditorController::handleInputForState4(int key)
{
    if (key == GLFW_KEY_F25)
    {
        state = 1;
        view->setState(state);
    }
    if (key == GLFW_KEY_ENTER)
    {
        std::string targetPath = static_cast<std::string>(RESOURCE_DIR).append(view->getTargetPath());
        saveGridAsBinaryFile(targetPath, grid);
        state = 1;
        view->setState(state);
    }
}
void EditorController::handleInputForState5(int key)
{
    if (key == GLFW_KEY_F25)
    {
        state = 1;
        view->setState(state);
    }
}
void EditorController::handleInputForState6(int key)
{
    if (key == GLFW_KEY_F25)
    {
        state = 5;
        view->setState(state);
    }
}
void EditorController::handleInputForState7(int key)
{
    if (key == GLFW_KEY_F25)
    {
        state = 6;
        view->setState(state);
    }
}
void EditorController::eraseMobAt(int focussedX, int focussedY)
{

    std::vector<Mob *> *mobs = grid->getMobs();
    for (int i = 0; i < mobs->size(); i++)
    {
        if (mobs->at(i)->getPosX() == focussedX && mobs->at(i)->getPosY() == focussedY)
        {
            mobs->erase(mobs->begin() + i);
        }
    }
}
void EditorController::setWindowClosed(bool closed)
{
    exit = closed;
}