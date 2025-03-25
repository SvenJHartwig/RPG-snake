#include "scene.h"

namespace SEngine
{
    int Scene::currentId = 0;
    int Scene::getId() { return id; }
    Scene::Scene()
    {
        scene_elements = new std::vector<SEngine::Element *>();
        this->id = currentId++;
    }
    Scene::~Scene() {}
}