#pragma once

#include "../iEngineCallback.h"
#include "../renderData.h"
#include <functional>

namespace SEngine
{
    inline void empty(IEngineCallback *gc, int) {}
    class Element : public IEngineCallback
    {
    protected:
        bool isHovered = false;
        bool visible = true;
        bool focussed = false;
        int pos_x_top_left;
        int pos_y_top_left;
        int pos_x_bottom_right;
        int pos_y_bottom_right;

    public:
        void (*callback)(IEngineCallback *, int) = &empty;
        void setIsHovered(bool isHovered);
        void setFocussed(bool focussed);
        void setVisible(bool visible);
        bool getVisible();
        int getPosXTopLeft();
        int getPosYTopLeft();
        int getPosXBottomRight();
        int getPosYBottomRight();
        virtual void click(IEngineCallback *callback, int x, int y) = 0;
        virtual RenderData *createRenderData() = 0;
        ~Element() {}
    };
}