#pragma once

#include "../view/editorView.h"
#include "../../commonFunctions.h"
#include "../../editor/loadTextFile.h"
#include "../../model/mob.h"
#include "../../model/teleporter.h"

class EditorController : public SEngine::IEngineCallback
{
private:
    IEditorView *view;

public:
    bool exit = false;
    std::string input;
    /*
     * States:
     * 0 - Initial
     * 1 - Map loaded
     * 2 - Choosing what element to add
     * 3 - Teleporter selecte, choosing parameters
     */
    int state = 0;
    std::string path = RESOURCE_DIR;
    Grid *grid;
    int x;
    int y;
    EditorController(IEditorView *view);
    ~EditorController();
    void mainLoop();
    void mainLoopIteration();
    void reactOnInput(int input);
    void eraseMobAt(int focussedX, int focussedY);
    void setWindowClosed(bool closed);
    std::vector<std::vector<SEngine::Sprite> *> *getSpriteVector();
};