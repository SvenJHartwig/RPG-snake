#include "button.h"

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
    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(pos_x_top_left, pos_y_top_left);
    glVertex2i(pos_x_top_left, pos_y_bottom_right);
    glVertex2i(pos_x_bottom_right, pos_y_top_left);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(pos_x_top_left, pos_y_bottom_right);
    glVertex2i(pos_x_bottom_right, pos_y_top_left);
    glVertex2i(pos_x_bottom_right, pos_y_bottom_right);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    print(*fd, pos_x_top_left, pos_y_bottom_right, text);
}