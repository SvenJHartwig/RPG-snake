#include "renderData.h"

namespace SEngine
{
    RenderData::RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }

    RenderData::RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::string &text, float x, float y, float textWidth, float textMaxHeight, glm::vec3 color)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->text = text;
        this->textPosX = x;
        this->textPosY = y;
        this->textWidth = textWidth;
        this->textMaxHeight = textMaxHeight;
        this->textColor = color;
    }

    RenderData::RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, unsigned int texture)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->texture = texture;
        hasTexture = true;
    }

    RenderData::RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::string &text, float x, float y, float textWidth, float textMaxHeight, glm::vec3 color, unsigned int texture)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->text = text;
        this->textPosX = x;
        this->textPosY = y;
        this->textWidth = textWidth;
        this->textMaxHeight = textMaxHeight;
        this->textColor = color;
        this->texture = texture;
        hasTexture = true;
    }

    std::vector<float> RenderData::getVertices() { return vertices; }
    std::vector<unsigned int> RenderData::getIndices() { return indices; }
    std::string RenderData::getText() { return text; }
    float RenderData::getTextPosX() { return textPosX; }
    float RenderData::getTextPosY() { return textPosY; }
    float RenderData::getTextWidth() { return textWidth; }
    float RenderData::getTextMaxHeight() { return textMaxHeight; }
    bool RenderData::getHasTexture() { return hasTexture; }
    unsigned int RenderData::getTexture() { return texture; }
    glm::vec3 RenderData::getTextColor() { return textColor; }
}