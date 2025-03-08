#include "textInput.h"
#include <vector>

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
    }
    TextInput::~TextInput() {}
    RenderData *TextInput::createRenderData()
    {
        vector<float> vertices = {};
        vector<unsigned int> indices = {};
        if (focussed)
        {
            return new RenderData(vertices, indices, text, pos_x_top_left, pos_y_bottom_right, (float)pos_x_bottom_right - pos_x_top_left, (float)pos_y_bottom_right - pos_y_top_left, glm::vec3(0.5f, 0.5f, 0.5f));
        }
        else
        {
            return new RenderData(vertices, indices, text, pos_x_top_left, pos_y_bottom_right, (float)pos_x_bottom_right - pos_x_top_left, (float)pos_y_bottom_right - pos_y_top_left, glm::vec3(0.0f, 1.0f, 1.0f));
        }
    }
    void TextInput::reactOnInput(int input)
    {
        if (input == GLFW_MOUSE_BUTTON_1)
        {
            focussed = true;
        }
        if (input == GLFW_KEY_BACKSPACE && text.size() > 0)
        {
            text.erase(text.size() - 1, text.size());
        }
        else if (focussed)
        {
            text += static_cast<char>(input);
        }
    }
    void TextInput::setWindowClosed(bool closed)
    {
    }
}