#include "text.h"

using std::vector;

namespace SEngine
{
    Text::Text(int pos_x_top_left,
               int pos_y_top_left,
               int pos_x_bottom_right,
               int pos_y_bottom_right)
    {
        this->pos_x_top_left = pos_x_top_left;
        this->pos_y_top_left = pos_y_top_left;
        this->pos_x_bottom_right = pos_x_bottom_right;
        this->pos_y_bottom_right = pos_y_bottom_right;
    }

    Text::~Text() {}

    RenderData *Text::createRenderData()
    {
        vector<float> vertices = {};
        vector<unsigned int> indices = {};
        return new RenderData(vertices, indices, text, pos_x_top_left, pos_y_bottom_right, (float)pos_x_bottom_right - pos_x_top_left, (float)pos_y_bottom_right - pos_y_top_left, glm::vec3(1.0f, 1.0f, 1.0f));
    }
}