#include "image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../iRenderEngine.h"
#include "../includes/stb_image.h"

using std::vector;

namespace SEngine
{
    Image::Image(int pos_x_top_left,
                 int pos_y_top_left,
                 int pos_x_bottom_right,
                 int pos_y_bottom_right,
                 std::string path,
                 StretchMode stretchMode)
    {
        this->pos_x_top_left = pos_x_top_left;
        this->pos_y_top_left = pos_y_top_left;
        this->pos_x_bottom_right = pos_x_bottom_right;
        this->pos_y_bottom_right = pos_y_bottom_right;
        this->texture = IRenderEngine::createTexture(path);
        this->stretchMode = stretchMode;
        stbi_load(path.c_str(), &width, &height, &height, 0);
    }
    void Image::click(IEngineCallback *callback) { this->callback(callback, GLFW_MOUSE_BUTTON_1); }
    void Image::reactOnInput(int input) {}
    void Image::setWindowClosed(bool closed) {}

    RenderData *Image::createRenderData()
    {
        float textureFractionWidth = computeTextureFraction(width, pos_x_top_left - pos_x_bottom_right);
        float textureFractionHeight = computeTextureFraction(height, pos_y_top_left - pos_y_bottom_right);
        vector<float> vertices = {
            pos_x_top_left * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            pos_x_top_left * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, textureFractionHeight,
            pos_x_bottom_right * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, textureFractionWidth, 0.0f,
            pos_x_bottom_right * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, textureFractionWidth, textureFractionHeight};
        vector<unsigned int> indices = {
            0, 1, 2,
            1, 2, 3};
        RenderData *data;
        data = new RenderData(vertices, indices, texture);
        return data;
    }
    float Image::computeTextureFraction(int sizeFile, int sizeImage)
    {
        if (stretchMode == StretchMode::FIT_TO_SIZE)
        {
            return 1.0f;
        }
        return (float)sizeImage / (float)sizeFile;
    }
}