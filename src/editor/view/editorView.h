#pragma once
#include <string>
#include "../../view/engine/iRenderEngine.h"
#include "../../view/engine/elements/scene.h"
#include "../../view/engine/iEngineCallback.h"
#include "../../view/engine/elements/spriteGrid.h"
#include "../../view/engine/elements/button.h"

class IEditorView
{
public:
    virtual std::string showOutput(std::string out) = 0;
    virtual int init() = 0;
    virtual void setCallback(SEngine::IEngineCallback *callback) = 0;
    virtual std::string getText() = 0;
    virtual void setState(int state) = 0;
    virtual void setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid) = 0;
    virtual int getFocussedSpriteX() = 0;
    virtual int getFocussedSpriteY() = 0;
};

class EditorView : public IEditorView
{
private:
    bool initialized = false;
    SEngine::IRenderEngine *engine = NULL;
    SEngine::Scene *loadingScene = NULL;
    SEngine::Scene *editorScene = NULL;
    SEngine::IEngineCallback *callback = NULL;
    SEngine::SpriteGrid *grid;
    SEngine::Button *saveButton;
    SEngine::Button *wallButton;
    SEngine::Button *groundButton;
    SEngine::Button *enemyButton;
    SEngine::Button *tpButton;

public:
    bool
    isInitialized()
    {
        return initialized;
    }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    std::string showOutput(std::string out);
    EditorView();
    int init() override;
    void initLoadingScene();
    void initEditorScene();
    SEngine::Scene *getLoadingScene() { return loadingScene; }
    void setCallback(SEngine::IEngineCallback *callback);
    SEngine::IEngineCallback *getCallback();
    int getFocussedSpriteX();
    int getFocussedSpriteY();
    std::string getText();
    void setState(int state);
    void setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid);
};