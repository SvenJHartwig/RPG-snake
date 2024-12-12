#include "button.h"
#include "../iRenderEngine.h"

namespace SEngine
{
    using std::vector;

    Button::Button(int pos_x_top_left,
                   int pos_y_top_left,
                   int pos_x_bottom_right,
                   int pos_y_bottom_right)
    {
        this->pos_x_top_left = pos_x_top_left;
        this->pos_y_top_left = pos_y_top_left;
        this->pos_x_bottom_right = pos_x_bottom_right;
        this->pos_y_bottom_right = pos_y_bottom_right;

        std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/button.png");
        texture = IRenderEngine::createTexture(texturePath);
    }

    RenderData *Button::createRenderData()
    {
        vector<float> vertices = {
            // x, y
            pos_x_top_left * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            pos_x_top_left * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            pos_x_bottom_right * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            pos_x_bottom_right * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
        vector<unsigned int> indices = {
            0, 1, 2, // First triangle
            1, 2, 3  // Second triangle
        };

        RenderData *data = new RenderData(vertices, indices, text, pos_x_top_left + 2, pos_y_bottom_right - 8, (float)pos_x_bottom_right - pos_x_top_left - 8, (float)pos_y_bottom_right - pos_y_top_left - 8, glm::vec3(0.0f, 0.0f, 1.0f), texture);
        return data;
    }
}