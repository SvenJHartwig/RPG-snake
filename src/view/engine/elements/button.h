#pragma once
#include <string>
#include "../TextRenderer/TextRenderer.h"
#include "element.h"

namespace SEngine
{
    class Button : public Element
    {
    private:
        unsigned int textureNotHovered;
        unsigned int textureHovered;

    public:
        std::string text;
        Button(int pos_x_top_left,
               int pos_y_top_left,
               int pos_x_bottom_right,
               int pos_y_bottom_right);
        ~Button();
        void click(IEngineCallback *callback) override;
        RenderData *createRenderData() override;
    };
}