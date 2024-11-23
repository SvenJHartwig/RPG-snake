#include "renderEngine.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderData.h"
#include <unistd.h>

using std::string;

// Vertex shader source code
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor; 

out vec3 vertexColor;

uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
    vertexColor = aColor;
}
)";

// Fragment shader source code
const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vec4(vertexColor, 1.0);
} 
)";

// Callback for resizing the window
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Compile shader and check for errors
GLuint compileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    }
    return shader;
}

// Link shaders into a program
GLuint createShaderProgram(const char *vertexSource, const char *fragmentSource)
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
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
        glUseProgram(shaderProgram);

        for (int i = 0; i < currentScene->scene_elements->size(); i++)
        {
            RenderData *data = currentScene->scene_elements->at(i)->createRenderData();

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            // Update buffers with new vertex data
            glBufferData(GL_ARRAY_BUFFER, data->getVertices().size() * sizeof(float), data->getVertices().data(), GL_DYNAMIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->getIndices().size() * sizeof(float), data->getIndices().data(), GL_STATIC_DRAW);

            // Draw rectangle
            glDrawElements(GL_TRIANGLES, data->getVertices().size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        textRenderer->RenderText(*textShader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    callback->setWindowClosed(true);
    glfwTerminate();
}

int RenderEngine::init()
{
    int error = 0;
    if (!glfwInit())
    {
        error = -1;
    }

    // Create a window
    window = glfwCreateWindow(1024, 768, "Snake", NULL, NULL);
    if (!window)
    {
        error = -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        error = -1;
    }

    // Initialize input callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, engine_key_callback);
    glfwSetMouseButtonCallback(window, engine_mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Rectangle data in screen coordinates
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shaderProgram);

    // Set up orthographic projection matrix
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
    GLint projLoc = glGetUniformLocation(shaderProgram, "uProjection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    string pathToVs = RESOURCE_DIR;
    pathToVs.append("/shaders/text.vs");
    string pathToFs = RESOURCE_DIR;
    pathToFs.append("/shaders/text.fs");
    textShader = new Shader(pathToVs.c_str(), pathToFs.c_str());
    glm::mat4 textProjection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
    textShader->use();
    glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(textProjection));
    textRenderer = new TextRenderer();
    if (textRenderer->init() != 0)
    {
        error = -2;
    }

    if (error != 0)
    {
        callback->setWindowClosed(true);
        glfwTerminate();
    }

    return 0;
}