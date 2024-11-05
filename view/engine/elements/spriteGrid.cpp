#include "spriteGrid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

SpriteGrid::SpriteGrid(int pos_x_top_left,
                       int pos_y_top_left,
                       int pos_x_bottom_right,
                       int pos_y_bottom_right)
{
    this->pos_x_top_left = pos_x_top_left;
    this->pos_y_top_left = pos_y_top_left;
    this->pos_x_bottom_right = pos_x_bottom_right;
    this->pos_y_bottom_right = pos_y_bottom_right;
}
void SpriteGrid::render()
{
    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < grid->at(i).size(); j++)
        {
            glBegin(GL_TRIANGLE_FAN);
            switch (grid->at(i)[j])
            {
            case 'W':
                glColor3f(0.9f, 0.9f, 0.9f);
                break;
            case 'H':
                glColor3f(0.9f, 0.2f, 0.2f);
                break;
            case 'B':
                glColor3f(0.8f, 0.2f, 0.2f);
                break;
            case 'F':
                glColor3f(0.2f, 0.9f, 0.2f);
                break;
            case 'S':
                glColor3f(0.1f, 0.1f, 0.9f);
                break;

            default:
                glColor3f(0.0f, 0.0f, 0.0f);
                break;
            }
            glVertex2i(pos_x_top_left + j * 32, pos_y_top_left - i * 32);
            glVertex2i(pos_x_top_left + j * 32 + 32, pos_y_top_left - i * 32);
            glVertex2i(pos_x_top_left + j * 32, pos_y_top_left - i * 32 + 32);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glVertex2i(pos_x_top_left + j * 32 + 32, pos_y_top_left - i * 32);
            glVertex2i(pos_x_top_left + j * 32, pos_y_top_left - i * 32 + 32);
            glVertex2i(pos_x_top_left + j * 32 + 32, pos_y_top_left - i * 32 + 32);
            glEnd();
        }
    }
}
