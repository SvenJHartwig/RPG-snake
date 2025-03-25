#pragma once

#include <vector>
#include "element.h"

namespace SEngine
{
    class Scene
    {
    private:
        static int currentId;
        int id;

    public:
        int getId();
        std::vector<Element *> *scene_elements;
        Scene();
        ~Scene();
    };
}