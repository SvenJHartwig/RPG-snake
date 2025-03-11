#include "spriteGrid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../iRenderEngine.h"

using std::vector;

namespace SEngine
{
    void SpriteGrid::initValues(int pos_x_top_left,
                                int pos_y_top_left,
                                int pos_x_bottom_right,
                                int pos_y_bottom_right)
    {
        this->pos_x_top_left = pos_x_top_left;
        this->pos_y_top_left = pos_y_top_left;
        this->pos_x_bottom_right = pos_x_bottom_right;
        this->pos_y_bottom_right = pos_y_bottom_right;
    }
    void SpriteGrid::initValues(int pos_x_top_left,
                                int pos_y_top_left,
                                int pos_x_bottom_right,
                                int pos_y_bottom_right,
                                const std::string &textureMapPath,
                                float spriteFraction)
    {
        initValues(pos_x_top_left,
                   pos_y_top_left,
                   pos_x_bottom_right,
                   pos_y_bottom_right);
        this->textureMap = IRenderEngine::createTexture(textureMapPath);
        this->spriteFraction = spriteFraction;
        this->grid = new std::vector<std::vector<Sprite> *>();
    }
    SpriteGrid::SpriteGrid(int pos_x_top_left,
                           int pos_y_top_left,
                           int pos_x_bottom_right,
                           int pos_y_bottom_right)
    {
        initValues(pos_x_top_left,
                   pos_y_top_left,
                   pos_x_bottom_right,
                   pos_y_bottom_right);
    }
    SpriteGrid::SpriteGrid(int pos_x_top_left,
                           int pos_y_top_left,
                           int pos_x_bottom_right,
                           int pos_y_bottom_right,
                           const std::string &textureMapPath,
                           float spriteFraction)
    {
        initValues(pos_x_top_left,
                   pos_y_top_left,
                   pos_x_bottom_right,
                   pos_y_bottom_right,
                   textureMapPath,
                   spriteFraction);
    }
    void SpriteGrid::click(IEngineCallback *callback, int x, int y)
    {
        focussedSpriteX = x / 32;
        focussedSpriteY = y / 32;
        this->callback(callback, GLFW_MOUSE_BUTTON_1);
    }
    void SpriteGrid::reactOnInput(int input) {}
    void SpriteGrid::setWindowClosed(bool closed) {}

    RenderData *SpriteGrid::createRenderData()
    {
        vector<float> vertices = {};
        vector<unsigned int> indices = {};
        RenderData *data;
        if (grid == NULL)
        {
            return data;
        }
        for (int i = 0; i < grid->size(); i++)
        {
            for (int j = 0; j < grid->at(i)->size(); j++)
            {
                float c1 = 0.0f, c2 = 0.0f, c3 = 0.0f;
                float texBaseX = grid->at(i)->at(j).texBaseX;
                float texBaseY = grid->at(i)->at(j).texBaseY;
                // Insert four vertices for the current rectangle
                vertices.insert(vertices.end(), {(float)pos_x_top_left + j * 32, (float)pos_y_top_left + i * 32, c1, c2, c3, texBaseX, texBaseY,
                                                 (float)pos_x_top_left + j * 32 + 32, (float)pos_y_top_left + i * 32, c1, c2, c3, texBaseX + spriteFraction, texBaseY,
                                                 (float)pos_x_top_left + j * 32, (float)pos_y_top_left + i * 32 + 32, c1, c2, c3, texBaseX, texBaseY + spriteFraction,
                                                 (float)pos_x_top_left + j * 32 + 32, (float)pos_y_top_left + i * 32 + 32, c1, c2, c3, texBaseX + spriteFraction, texBaseY + spriteFraction});

                // Indices for the current rectangle
                int baseIndex = (i * grid->at(i)->size() + j) * 4;
                indices.push_back(baseIndex);
                indices.push_back(baseIndex + 1);
                indices.push_back(baseIndex + 2);
                indices.push_back(baseIndex + 1);
                indices.push_back(baseIndex + 2);
                indices.push_back(baseIndex + 3);
            }
        }
        if (textureMap == 0)
        {
            data = new RenderData(vertices, indices);
        }
        else
        {
            data = new RenderData(vertices, indices, textureMap);
        }
        return data;
    }
    void SpriteGrid::setGrid(std::vector<std::vector<Sprite> *> *grid) { this->grid = grid; }
    std::vector<std::vector<Sprite> *> *SpriteGrid::getGrid() { return grid; }
    int SpriteGrid::getFocussedSpriteX() { return focussedSpriteX; }
    int SpriteGrid::getFocussedSpriteY() { return focussedSpriteY; }
}