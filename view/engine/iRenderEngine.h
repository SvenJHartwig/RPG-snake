#pragma once
#include "../../TextRenderer/TextRenderer.h"

class IRenderEngine
{
public:
    virtual IEngineCallback *getEngineCallback() = 0;
    virtual void setEngineCallback(IEngineCallback *callback) = 0;
    virtual Scene *getCurrentScene() = 0;
    virtual GLFWwindow *getWindow() = 0;
    virtual void setCurrentScene(Scene *currentScene) = 0;
    virtual void renderingLoop() = 0;
    virtual int init() = 0;
    virtual font_data *getFontData() = 0;
};