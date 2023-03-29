#include "src/GLCall.h"
#include "src/RenderObject.h"
#include "src/Shader.h"
#include "src/Texture.h"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    int windowWidth = 1200;
    int windowHeight = 800;
    window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //glfwSetKeyCallback(window, key_callback);
    //glfwSetMouseButtonCallback(window, mouse_button_callback);
    //glfwSetCursorPosCallback(window, cursor_position_callback);
    //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glFrontFace(GL_CCW));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "Version: " << glfwGetVersionString() << std::endl;

    float data[16] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f,//Bot left
         0.5f, -0.5f, 1.0f, 0.0f,//Bot right
         0.5f,  0.5f, 1.0f, 1.0f,//Top right
        -0.5f,  0.5f, 0.0f, 1.0f //Top left
    };

    unsigned int indexBufferData[6] =
    {
        0, 1, 2,
        2, 3, 0
    };

    Shader shader("Boulder/res/Shaders/Basic.shader", false);
    shader.Bind();

    Texture testTexture("Boulder/res/Textures/blue_circle.png");
    testTexture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    RenderObject ro(data, 16, indexBufferData, 6);
    ro.SetTransformPosition(0, 0);

    std::vector<RenderObject*> renderObjects;
    renderObjects.push_back(&ro);

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    float aspectRatio = (float)windowWidth / (float)windowHeight;
    float projWidth = 4.0f;
    float projHeight = projWidth / aspectRatio;
    glm::mat4 projectionMatrix = glm::ortho(-projWidth / 2, projWidth / 2, -projHeight / 2, projHeight / 2, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.14f, 0.5f, 0.85f, 1.0f));

        shader.SetUniformMat4f("u_v", viewMatrix);
        shader.SetUniformMat4f("u_p", projectionMatrix);
        
        for (int i = 0; i < renderObjects.size(); i++)
        {
            renderObjects[i]->Bind();
            shader.SetUniformMat4f("u_m", *renderObjects[i]->GetTransformMatrix());
        }

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}