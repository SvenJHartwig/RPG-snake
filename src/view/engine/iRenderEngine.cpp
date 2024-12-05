#include "iRenderEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

unsigned int IRenderEngine::createTexture(std::string path)
{
    unsigned int result;
    int width, height, nrChannels;
    glGenTextures(1, &result);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, result);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        // Match internal format to number of channels
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Failed to load texture from path: " << path << std::endl;
    }
    return result;
}