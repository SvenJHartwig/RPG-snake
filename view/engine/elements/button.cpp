#include "button.h"
#include "../../../TextRenderer/TextRenderer.h"

Button::Button(int pos_x_top_left,
               int pos_y_top_left,
               int pos_x_bottom_right,
               int pos_y_bottom_right)
{
    this->pos_x_top_left = pos_x_top_left;
    this->pos_y_top_left = pos_y_top_left;
    this->pos_x_bottom_right = pos_x_bottom_right;
    this->pos_y_bottom_right = pos_y_bottom_right;
}
void Button::render()
{
    print(*fd, pos_x_top_left, pos_y_top_left, text);
}