#pragma once

#include "../iEngineCallback.h"
#include "../renderData.h"
#include <functional>

namespace SEngine
{
    inline void empty(IEngineCallback *gc, int) {}
    class Element
    {
    protected:
        bool isHovered = false;
        int pos_x_top_left;
        int pos_y_top_left;
        int pos_x_bottom_right;
        int pos_y_bottom_right;

    public:
        void (*callback)(IEngineCallback *, int) = &empty;
        void setIsHovered(bool isHovered);
        int getPosXTopLeft();
        int getPosYTopLeft();
        int getPosXBottomRight();
        int getPosYBottomRight();
        virtual RenderData *createRenderData() = 0;
        ~Element() {}
    };
}