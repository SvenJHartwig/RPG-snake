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

RenderData *SpriteGrid::createRenderData()
{
    vector<float> vertices = {};
    vector<unsigned int> indices = {};
    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < grid->at(i).size(); j++)
        {
            float c1, c2, c3;
            switch (grid->at(i)[j])
            {
            case 'W':
                c1 = 0.9f;
                c2 = 0.9f;
                c3 = 0.9f;
                break;
            case 'H':
                c1 = 0.9f;
                c2 = 0.2f;
                c3 = 0.2f;
                break;
            case 'B':
                c1 = 0.8f;
                c2 = 0.2f;
                c3 = 0.2f;
                break;
            case 'F':
                c1 = 0.2f;
                c2 = 0.9f;
                c3 = 0.2f;
                break;
            case 'S':
                c1 = 0.1f;
                c2 = 0.1f;
                c3 = 0.9f;
                break;

            default:
                c1 = 0.2f;
                c2 = 0.2f;
                c3 = 0.2f;
                break;
            }
            vertices.push_back(pos_x_top_left + j * 32);
            vertices.push_back(pos_y_top_left + i * 32);
            vertices.push_back(c1);
            vertices.push_back(c2);
            vertices.push_back(c3);
            vertices.push_back(pos_x_top_left + j * 32 + 32);
            vertices.push_back(pos_y_top_left + i * 32);
            vertices.push_back(c1);
            vertices.push_back(c2);
            vertices.push_back(c3);
            vertices.push_back(pos_x_top_left + j * 32);
            vertices.push_back(pos_y_top_left + i * 32 + 32);
            vertices.push_back(c1);
            vertices.push_back(c2);
            vertices.push_back(c3);
            vertices.push_back(pos_x_top_left + j * 32 + 32);
            vertices.push_back(pos_y_top_left + i * 32 + 32);
            vertices.push_back(c1);
            vertices.push_back(c2);
            vertices.push_back(c3);
            int baseIndex = (i * grid->at(i).size() + j) * 4;
            indices.push_back(baseIndex);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 3);
        }
    }
    RenderData *data = new RenderData(vertices, indices);
    return data;
}
