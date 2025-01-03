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

        textureNotHovered = IRenderEngine::createTexture(((std::string)RESOURCE_DIR).append("/textures/button.png"));
        textureHovered = IRenderEngine::createTexture(((std::string)RESOURCE_DIR).append("/textures/button-pressed.png"));
    }

    RenderData *Button::createRenderData()
    {
        vector<float> vertices = {
            // Left part of the button
            pos_x_top_left * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            pos_x_top_left * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            pos_x_top_left * 1.0f + 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 0.0f,
            pos_x_top_left * 1.0f + 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 1.0f,

            // Middle part of the button
            pos_x_top_left * 1.0f + 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 0.0f,
            pos_x_top_left * 1.0f + 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 1.0f,
            pos_x_bottom_right * 1.0f - 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.75f, 0.0f,
            pos_x_bottom_right * 1.0f - 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.75f, 1.0f,

            // Right part of the button
            pos_x_bottom_right * 1.0f - 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.75f, 0.0f,
            pos_x_bottom_right * 1.0f - 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.75f, 1.0f,
            pos_x_bottom_right * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            pos_x_bottom_right * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
        vector<unsigned int> indices = {
            0, 1, 2,
            1, 2, 3,
            4, 5, 6,
            5, 6, 7,
            8, 9, 10,
            9, 10, 11};

        unsigned int currentTexture;
        if (isHovered)
        {
            currentTexture = textureHovered;
        }
        else
        {
            currentTexture = textureNotHovered;
        }
        RenderData *data = new RenderData(vertices, indices, text, pos_x_top_left + 2, pos_y_bottom_right - 8, (float)pos_x_bottom_right - pos_x_top_left - 8, (float)pos_y_bottom_right - pos_y_top_left - 8, glm::vec3(0.0f, 0.0f, 1.0f), currentTexture);
        return data;
    }
}