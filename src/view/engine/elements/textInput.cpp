#include "textInput.h"
#include <vector>
#include "../iRenderEngine.h"

using std::vector;

namespace SEngine
{
    void inputKey(IEngineCallback *gc, int key)
    {
        gc->reactOnInput(key);
    }
    TextInput::TextInput(int pos_x_top_left,
                         int pos_y_top_left,
                         int pos_x_bottom_right,
                         int pos_y_bottom_right)
    {
        this->pos_x_top_left = pos_x_top_left;
        this->pos_y_top_left = pos_y_top_left;
        this->pos_x_bottom_right = pos_x_bottom_right;
        this->pos_y_bottom_right = pos_y_bottom_right;
        focussed = false;
        this->callback = &inputKey;

        // ToDo: Create texture for textinput
        textureNotHovered = IRenderEngine::createTexture(((std::string)RESOURCE_DIR).append("/textures/button.png"));
        textureHovered = IRenderEngine::createTexture(((std::string)RESOURCE_DIR).append("/textures/button-pressed.png"));
    }
    TextInput::~TextInput() {}
    void TextInput::click(IEngineCallback *callback, int x, int y)
    {
        this->callback(callback, GLFW_MOUSE_BUTTON_1);
        focussed = true;
    }
    void TextInput::reactOnInput(int input)
    {
        if (input == GLFW_KEY_ESCAPE)
        {
            focussed = false;
        }
        if (input == GLFW_KEY_BACKSPACE && text.size() > 0)
        {
            text.pop_back();
        }
        else if (focussed && input != GLFW_KEY_BACKSPACE)
        {
            text += static_cast<char>(input);
        }
    }
    void TextInput::setWindowClosed(bool closed) {}
    RenderData *TextInput::createRenderData()
    {
        vector<float> vertices = {
            // Left part of the texture
            pos_x_top_left * 1.0f, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            pos_x_top_left * 1.0f, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            pos_x_top_left * 1.0f + 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 0.0f,
            pos_x_top_left * 1.0f + 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 1.0f,

            // Middle part of the texture
            pos_x_top_left * 1.0f + 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 0.0f,
            pos_x_top_left * 1.0f + 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.25f, 1.0f,
            pos_x_bottom_right * 1.0f - 4, pos_y_top_left * 1.0f, 1.0f, 0.0f, 0.0f, 0.75f, 0.0f,
            pos_x_bottom_right * 1.0f - 4, pos_y_bottom_right * 1.0f, 1.0f, 0.0f, 0.0f, 0.75f, 1.0f,

            // Right part of the texture
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

        if (focussed)
        {
            return new RenderData(vertices, indices, text, pos_x_top_left, pos_y_bottom_right, (float)pos_x_bottom_right - pos_x_top_left, (float)pos_y_bottom_right - pos_y_top_left, glm::vec3(0.0f, 0.0f, 0.0f), textureHovered);
        }
        else
        {
            return new RenderData(vertices, indices, text, pos_x_top_left, pos_y_bottom_right, (float)pos_x_bottom_right - pos_x_top_left, (float)pos_y_bottom_right - pos_y_top_left, glm::vec3(0.0f, 0.0f, 0.0f), textureNotHovered);
        }
    }
}