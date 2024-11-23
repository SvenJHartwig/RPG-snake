#pragma once

#include <vector>
#include "glm/glm.hpp"
#include <string>

using std::vector;

class RenderData
{
private:
    vector<float> vertices;
    vector<unsigned int> indices;
    std::string text = "";
    float textPosX;
    float textPosY;
    float textScale;
    glm::vec3 textColor;

public:
    RenderData(vector<float> vertices, vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }
    RenderData(vector<float> vertices, vector<unsigned int> indices, std::string text, float x, float y, float scale, glm::vec3 color)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->text = text;
        this->textPosX = x;
        this->textPosY = y;
        this->textScale = scale;
        this->textColor = color;
    }
    vector<float> getVertices() { return vertices; }
    vector<unsigned int> getIndices() { return indices; }
    std::string getText() { return text; }
    float getTextPosX() { return textPosX; }
    float getTextPosY() { return textPosY; }
    float getTextScale() { return textScale; }
    glm::vec3 getTextColor() { return textColor; }
};