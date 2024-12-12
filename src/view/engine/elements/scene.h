#pragma once

#include <vector>
#include "element.h"

namespace SEngine
{
    class Scene
    {
    public:
        std::vector<Element *> *scene_elements;
    };
}