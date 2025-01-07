#pragma once

#include <vector>
#include "glm/glm.hpp"
#include <string>

namespace SEngine
{
    // Holds the data necessary to render one OpenGL element.
    class RenderData
    {
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::string text = "";
        float textPosX = 0.0f;
        float textPosY = 0.0f;
        float textWidth = 0.0f;
        float textMaxHeight = 0.0f;
        glm::vec3 textColor;
        // If this is false, the color attribute is used instead of the texture attribute.
        bool hasTexture = false;
        unsigned int texture = 0;

    public:
        // Use for elements that have no texture and no text.
        // - vertices: Vertices of the element. Needs to be in the format of:
        // -- Two float values for position (x,y)
        // -- Three float values for the color (r,g,b)
        // -- Two float values for the texture position
        // - indices: Indices of the element. The element is rendered as triangles
        RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        // Use for elements that have no texture and text.
        // - vertices: Vertices of the element. Needs to be in the format of:
        // -- Two float values for position (x,y)
        // -- Three float values for the color (r,g,b)
        // -- Two float values for the texture position
        // - indices: Indices of the element. The element is rendered as triangles
        // - text: If this contains a non-empty string, the text is rendered with the values of the text variables.
        // - textWidth: Maximum width of the text in pixel. If the text would be wider than this, it is scaled down.
        // - textHeight: Maximum height of the text in pixel. If the text would be taller than this, it is scaled down.
        RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::string &text, float x, float y, float textWidth, float textMaxHeight, glm::vec3 color);
        // Use for elements that have a texture and no text.
        // - vertices: Vertices of the element. Needs to be in the format of:
        // -- Two float values for position (x,y)
        // -- Three float values for the color (r,g,b)
        // -- Two float values for the texture position
        // - indices: Indices of the element. The element is rendered as triangles
        // - texture: OpenGL generated texture number
        RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, unsigned int texture);
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
        RenderData(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::string &text, float x, float y, float textWidth, float textMaxHeight, glm::vec3 color, unsigned int texture);

        std::vector<float> getVertices();
        std::vector<unsigned int> getIndices();
        std::string getText();
        float getTextPosX();
        float getTextPosY();
        float getTextWidth();
        float getTextMaxHeight();
        bool getHasTexture();
        unsigned int getTexture();
        glm::vec3 getTextColor();
    };
}