#pragma once
#include <glm/glm.hpp>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../shaders/shader.h"

namespace SEngine
{
    struct Character
    {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;        // Size of glyph
        glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Offset to advance to next glyph
    };

    class TextRenderer
    {
        unsigned int VAO = 0, VBO = 0;
        unsigned int windowWidth = 0, windowHeight = 0;
        Shader *shader = NULL;
        std::map<char, Character> Characters;

    public:
        void RenderText(std::string text, float x, float y, float maxWidth, float maxHeight, glm::vec3 color);
        void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
        int init(unsigned int windowWidth, unsigned int windowHeight);
    };
}