#pragma once
#include <string>
#include "../../TextRenderer/TextRenderer.h"
#include "element.h"

class Button : public Element
{
private:
public:
    font_data *fd;
    std::string text;
    Button(int pos_x_top_left,
           int pos_y_top_left,
           int pos_x_bottom_right,
           int pos_y_bottom_right);
    ~Button();
    void render();
};