#include "renderEngine.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderData.h"
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

using std::string;

// Callback for resizing the window
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void engine_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
    {
        return;
    }
    RenderEngine *engine = static_cast<RenderEngine *>(glfwGetWindowUserPointer(window));
    switch (key)
    {
    case GLFW_KEY_RIGHT:
        engine->getEngineCallback()->reactOnInput('d');
        break;
    case GLFW_KEY_LEFT:
        engine->getEngineCallback()->reactOnInput('a');
        break;
    case GLFW_KEY_UP:
        engine->getEngineCallback()->reactOnInput('w');
        break;
    case GLFW_KEY_DOWN:
        engine->getEngineCallback()->reactOnInput('s');
        break;
    case GLFW_KEY_P:
        engine->getEngineCallback()->reactOnInput('p');
        break;
    case GLFW_KEY_L:
        engine->getEngineCallback()->reactOnInput('l');
        break;
    case GLFW_KEY_O:
        engine->getEngineCallback()->reactOnInput('o');
        break;
    }
}

void engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (action != GLFW_PRESS)
    {
        return;
    }
    RenderEngine *engine = static_cast<RenderEngine *>(glfwGetWindowUserPointer(window));
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    for (int i = 0; i < engine->getCurrentScene()->scene_elements->size(); i++)
    {
        Element *currentSceneElement = engine->getCurrentScene()->scene_elements->at(i);
        int xpostl = currentSceneElement->getPosXTopLeft();
        int ypostl = currentSceneElement->getPosYTopLeft();
        int xposbr = currentSceneElement->getPosXBottomRight();
        int yposbr = currentSceneElement->getPosYBottomRight();
        if (xpos > xpostl && xpos < xposbr &&
            ypos > ypostl && ypos < yposbr)
        {
            currentSceneElement->callback(engine->getEngineCallback());
        }
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void RenderEngine::renderingLoop()
{
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < currentScene->scene_elements->size(); i++)
        {
            RenderData *data = currentScene->scene_elements->at(i)->createRenderData();
            glBindTexture(GL_TEXTURE_2D, textureButton);

            // Bind normal buffers That are unbound during text rendering
            colorShader->use();
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // Update buffers with new vertex data
            glBufferData(GL_ARRAY_BUFFER, data->getVertices().size() * sizeof(float), data->getVertices().data(), GL_DYNAMIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->getIndices().size() * sizeof(float), data->getIndices().data(), GL_STATIC_DRAW);

            glDrawElements(GL_TRIANGLES, data->getVertices().size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            if (data->getText() != "")
            {
                textRenderer->RenderText(data->getText(), data->getTextPosX(), data->getTextPosY(), data->getTextScale(), data->getTextColor());
            }
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    callback->setWindowClosed(true);
    glfwTerminate();
}

int RenderEngine::init()
{
    /*********************************Set up OpenGL*************************************************/
    int error = 0;
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw" << std::endl;
    }

    // Create a window
    window = glfwCreateWindow(1024, 768, "Snake", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize glew" << std::endl;
    }

    // Initialize input callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, engine_key_callback);
    glfwSetMouseButtonCallback(window, engine_mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    /*************************Set up shaders*************************************** */
    string pathToVs = RESOURCE_DIR;
    pathToVs.append("/shaders/color.vs");
    string pathToFs = RESOURCE_DIR;
    pathToFs.append("/shaders/color.fs");
    colorShader = new Shader(pathToVs.c_str(), pathToFs.c_str());
    glActiveTexture(GL_TEXTURE0);
    colorShader->use();
    // Set up orthographic projection matrix for color shader
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(colorShader->ID, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // colorShader->setInt("ourTexture", 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    textureMap = createTexture(texturePath);

    texturePath = ((std::string)RESOURCE_DIR).append("/textures/button.png");
    textureButton = createTexture(texturePath);

    /****************************Set up text rendering***************************************************/

    textRenderer = new TextRenderer();
    if (textRenderer->init(windowWidth, windowHeight) != 0)
    {
        std::cerr << "Failed to initialize text renderer" << std::endl;
    }

    if (error != 0)
    {
        callback->setWindowClosed(true);
        glfwTerminate();
    }

    return 0;
}

unsigned int RenderEngine::createTexture(string path)
{
    unsigned int result;
    int width, height, nrChannels;
    glGenTextures(1, &result);
    glActiveTexture(GL_TEXTURE1);
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