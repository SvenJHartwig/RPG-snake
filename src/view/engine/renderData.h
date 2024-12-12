#pragma once

#include <vector>
#include "glm/glm.hpp"
#include <string>

// Holds the data necessary to render one OpenGL element.
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
    // If this is false, the color attribute is used instead of the texture attribute.
    bool hasTexture = false;
    unsigned int texture;

public:
    // Use for elements that have no texture and no text.
    // - vertices: Vertices of the element. Needs to be in the format of:
    // -- Two float values for position (x,y)
    // -- Three float values for the color (r,g,b)
    // -- Two float values for the texture position
    // - indices: Indices of the element. The element is rendered as triangles
    RenderData(std::vector<float> vertices, std::vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }
    // Use for elements that have no texture and text.
    // - vertices: Vertices of the element. Needs to be in the format of:
    // -- Two float values for position (x,y)
    // -- Three float values for the color (r,g,b)
    // -- Two float values for the texture position
    // - indices: Indices of the element. The element is rendered as triangles
    // - text: If this contains a non-empty string, the text is rendered with the values of the text variables.
    // - textWidth: Maximum width of the text in pixel. If the text would be wider than this, it is scaled down.
    // - textHeight: Maximum height of the text in pixel. If the text would be taller than this, it is scaled down.
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
    // Use for elements that have a texture and no text.
    // - vertices: Vertices of the element. Needs to be in the format of:
    // -- Two float values for position (x,y)
    // -- Three float values for the color (r,g,b)
    // -- Two float values for the texture position
    // - indices: Indices of the element. The element is rendered as triangles
    // - texture: OpenGL generated texture number
    RenderData(std::vector<float> vertices, std::vector<unsigned int> indices, unsigned int texture)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->texture = texture;
        hasTexture = true;
    }
    // Use for elements that have a texture and text.
    // - vertices: Vertices of the element. Needs to be in the format of:
    // -- Two float values for position (x,y)
    // -- Three float values for the color (r,g,b)
    // -- Two float values for the texture position
    // - indices: Indices of the element. The element is rendered as triangles
    // - texture: OpenGL generated texture number
    // - text: If this contains a non-empty string, the text is rendered with the values of the text variables.
    // - textWidth: Maximum width of the text in pixel. If the text would be wider than this, it is scaled down.
    // - textHeight: Maximum height of the text in pixel. If the text would be taller than this, it is scaled down.
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