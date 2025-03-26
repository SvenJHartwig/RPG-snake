#pragma once

#include "./engine/elements/scene.h"
#include "./engine/elements/text.h"
#include "./engine/iRenderEngine.h"

class Dialog
{
private:
    SEngine::IRenderEngine *engine;
    SEngine::Scene *dialogScene;
    SEngine::Text *textElement;

public:
    void show();
    void close();
    void setText(std::string text);
    Dialog(SEngine::IRenderEngine *engine, std::string text);
    ~Dialog();
};