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
     * 3 - Teleporter selected, choosing parameters
     * 4 - Save as selected, choosing file name
     */
    int state = 0;
    std::string path = RESOURCE_DIR;
    Grid *grid;
    int x;
    int y;
    EditorController(IEditorView *view);
    ~EditorController();
    void mainLoop();
    void reactOnInput(int input) override;
    void reactOnKeyReleased(int input) override;
    void handleInputForState0(int key);
    void handleInputForState1(int key);
    void handleInputForState2(int key);
    void handleInputForState3(int key);
    void handleInputForState4(int key);
    void eraseMobAt(int focussedX, int focussedY);
    void setWindowClosed(bool closed) override;
    std::vector<std::vector<SEngine::Sprite> *> *getSpriteVector();
};