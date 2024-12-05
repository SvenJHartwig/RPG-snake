#pragma once
#include "elements/scene.h"
#include "iEngineCallback.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unistd.h>
#include <iostream>

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
    static unsigned int createTexture(std::string path);
};