#pragma once

#include "element.h"
#include <vector>

namespace SEngine
{
    enum class StretchMode
    {
        FIT_TO_SIZE,
        ORIGINAL
    };

    class Image : public Element
    {
    private:
        int width, height;
        StretchMode stretchMode;
        unsigned int texture;

    public:
        Image(int pos_x_top_left,
              int pos_y_top_left,
              int pos_x_bottom_right,
              int pos_y_bottom_right,
              std::string path,
              StretchMode stretchMode = StretchMode::FIT_TO_SIZE);
        RenderData *createRenderData() override;
        float computeTextureFraction(int sizeFile, int sizeImage);
    };
}