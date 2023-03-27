#include "src/GLCall.h"
#include "src/RenderObject.h"

#include <iostream>
#include <string>

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
    window = glfwCreateWindow(1200, 800, "Hello World", NULL, NULL);
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

    float data[8] =
    {
        0.0f, 0.0f,//Bot left
        100.0f, 0.0f,//Bot right
        100.0f, 100.0f,//Top right
        0.0f, 100.0f
    };

    unsigned int indexBufferData[6] =
    {
        0, 1, 2,
        2, 3, 0
    };

    RenderObject ro(data, 8, indexBufferData, 6);

    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.14f, 0.5f, 0.85f, 1.0f));

        ro.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, nullptr));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}