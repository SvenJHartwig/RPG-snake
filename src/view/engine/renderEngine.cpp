#include "renderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderData.h"

namespace SEngine
{
    using std::string;

    bool sceneElementInCoords(Element *element, double xpos, double ypos)
    {
        int xpostl = element->getPosXTopLeft();
        int ypostl = element->getPosYTopLeft();
        int xposbr = element->getPosXBottomRight();
        int yposbr = element->getPosYBottomRight();
        if (xpos > xpostl && xpos < xposbr &&
            ypos > ypostl && ypos < yposbr)
        {
            return true;
        }
        return false;
    }

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
        engine->getEngineCallback()->reactOnInput(key);
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
        for (Scene *scene : *engine->getScenes())
        {
            for (int i = 0; i < scene->scene_elements->size(); i++)
            {
                Element *currentSceneElement = scene->scene_elements->at(i);
                if (sceneElementInCoords(currentSceneElement, xpos, ypos))
                {
                    currentSceneElement->callback(engine->getEngineCallback());
                    currentSceneElement->setIsHovered(false);
                }
            }
        }
    }
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
    {
        RenderEngine *engine = static_cast<RenderEngine *>(glfwGetWindowUserPointer(window));
        for (Scene *scene : *engine->getScenes())
        {
            for (int i = 0; i < scene->scene_elements->size(); i++)
            {
                Element *currentSceneElement = scene->scene_elements->at(i);
                currentSceneElement->setIsHovered(false);
                if (sceneElementInCoords(currentSceneElement, xpos, ypos))
                {
                    currentSceneElement->setIsHovered(true);
                }
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
            glActiveTexture(GL_TEXTURE0);

            for (Scene *scene : *currentScenes)
            {
                for (int i = 0; i < scene->scene_elements->size(); i++)
                {
                    RenderData *data = scene->scene_elements->at(i)->createRenderData();
                    if (data->getHasTexture())
                    {
                        glBindTexture(GL_TEXTURE_2D, data->getTexture());
                        textureShader->use();
                    }
                    else
                    {
                        glBindTexture(GL_TEXTURE_2D, 0);
                        colorShader->use();
                    }

                    // Bind normal buffers That are unbound during text rendering
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
                        textRenderer->RenderText(data->getText(), data->getTextPosX(), data->getTextPosY(), data->getTextWidth(), data->getTextMaxHeight(), data->getTextColor());
                    }
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
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Generate buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        /*************************Set up shaders*************************************** */

        // Set up orthographic projection matrix for shaders
        glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);

        colorShader = new Shader(static_cast<string>(RESOURCE_DIR).append("/shaders/color.vs").c_str(), static_cast<string>(RESOURCE_DIR).append("/shaders/color.fs").c_str());
        colorShader->use();
        initShader(colorShader, projection);
        textureShader = new Shader(static_cast<string>(RESOURCE_DIR).append("/shaders/texture.vs").c_str(), static_cast<string>(RESOURCE_DIR).append("/shaders/texture.fs").c_str());
        textureShader->use();
        initShader(textureShader, projection);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /****************************Set up text rendering***************************************************/

        textRenderer = new TextRenderer();
        if (textRenderer->init(windowWidth, windowHeight) != 0)
        {
            std::cerr << "Failed to initialize text renderer" << std::endl;
        }

        currentScenes = new std::vector<Scene *>();

        if (error != 0)
        {
            callback->setWindowClosed(true);
            glfwTerminate();
        }

        return 0;
    }
    void RenderEngine::initShader(Shader *shader, glm::mat4 projection)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}