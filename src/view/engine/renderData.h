#pragma once

#include <vector>
#include "glm/glm.hpp"
#include <string>

class RenderData
{
private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::string text = "";
    float textPosX;
    float textPosY;
    float textWidth;
    float textMaxHeight;
    glm::vec3 textColor;
    bool hasTexture = false;
    unsigned int texture;

public:
    RenderData(std::vector<float> vertices, std::vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }
    RenderData(std::vector<float> vertices, std::vector<unsigned int> indices, std::string text, float x, float y, float textWidth, float textMaxHeight, glm::vec3 color)
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
    RenderData(std::vector<float> vertices, std::vector<unsigned int> indices, unsigned int texture)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->texture = texture;
        hasTexture = true;
    }
    RenderData(std::vector<float> vertices, std::vector<unsigned int> indices, std::string text, float x, float y, float textWidth, float textMaxHeight, glm::vec3 color, unsigned int texture)
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
    std::vector<float> getVertices() { return vertices; }
    std::vector<unsigned int> getIndices() { return indices; }
    std::string getText() { return text; }
    float getTextPosX() { return textPosX; }
    float getTextPosY() { return textPosY; }
    float getTextWidth() { return textWidth; }
    float getTextMaxHeight() { return textMaxHeight; }
    bool getHasTexture() { return hasTexture; }
    unsigned int getTexture() { return texture; }
    glm::vec3 getTextColor() { return textColor; }
};