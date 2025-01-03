#include "image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../iRenderEngine.h"

using std::vector;

namespace SEngine
{
    Image::Image(int pos_x_top_left,
                 int pos_y_top_left,
                 int pos_x_bottom_right,
                 int pos_y_bottom_right,
                 std::string path)
    {
        this->pos_x_top_left = pos_x_top_left;
        this->pos_y_top_left = pos_y_top_left;
        this->pos_x_bottom_right = pos_x_bottom_right;
        this->pos_y_bottom_right = pos_y_bottom_right;
        this->texture = IRenderEngine::createTexture(path);
    }

    RenderData *Image::createRenderData()
    {
        vector<float> vertices = {
            pos_x_top_left * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            pos_x_top_left * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            pos_x_bottom_right * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            pos_x_bottom_right * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
        vector<unsigned int> indices = {
            0, 1, 2,
            1, 2, 3};
        RenderData *data;
        data = new RenderData(vertices, indices, texture);
        return data;
    }
}