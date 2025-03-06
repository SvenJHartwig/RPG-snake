#pragma once
#include <string>
#include "../../view/engine/iRenderEngine.h"
#include "../../view/engine/elements/scene.h"
#include "../../view/engine/iEngineCallback.h"

class IEditorView
{
public:
    virtual std::string showOutput(std::string out) = 0;
    virtual int init() = 0;
    virtual void setCallback(SEngine::IEngineCallback *callback) = 0;
    virtual std::string getText() = 0;
};

class EditorView : public IEditorView
{
private:
    bool initialized = false;
    SEngine::IRenderEngine *engine = NULL;
    SEngine::Scene *loadingScene = NULL;
    SEngine::IEngineCallback *callback = NULL;

public:
    bool isInitialized() { return initialized; }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    std::string showOutput(std::string out);
    EditorView();
    int init() override;
    void initLoadingScene();
    SEngine::Scene *getLoadingScene() { return loadingScene; }
    void setCallback(SEngine::IEngineCallback *callback);
    SEngine::IEngineCallback *getCallback();
    std::string getText();
};