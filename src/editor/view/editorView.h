#pragma once
#include <string>
#include "../../view/engine/iRenderEngine.h"

class IEditorView
{
public:
    virtual std::string showOutput(std::string out) = 0;
    virtual int init() = 0;
};

class EditorView : public IEditorView
{
private:
    bool initialized = false;
    SEngine::IRenderEngine *engine = NULL;

public:
    bool isInitialized() { return initialized; }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    std::string showOutput(std::string out);
    EditorView();
    int init() override;
};