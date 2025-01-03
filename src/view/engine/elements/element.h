#pragma once

#include "../iEngineCallback.h"
#include "../renderData.h"
#include <functional>

namespace SEngine
{
    class Element
    {
    protected:
        bool isHovered = false;
        int pos_x_top_left;
        int pos_y_top_left;
        int pos_x_bottom_right;
        int pos_y_bottom_right;

    public:
        void (*callback)(IEngineCallback *);
        void setIsHovered(bool isHovered) { this->isHovered = isHovered; }
        int getPosXTopLeft() { return pos_x_top_left; }
        int getPosYTopLeft() { return pos_y_top_left; }
        int getPosXBottomRight() { return pos_x_bottom_right; }
        int getPosYBottomRight() { return pos_y_bottom_right; }
        virtual RenderData *createRenderData() = 0;
        ~Element() {}
    };
}