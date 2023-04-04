#pragma once

#include "src/Scene.h"

#include <iostream>

int BoulderRun()
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

    Renderer renderer(windowWidth, windowHeight);
    Scene scene(&renderer);

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

    std::vector<std::unique_ptr<Shader>> shaders;
    //scope
    {
        std::unique_ptr<Shader> s(new Shader("res/Shaders/Basic.shader", false));
        shaders.push_back(std::move(s));
    }

    std::vector<std::unique_ptr<Texture>> textures;
    //scope
    {
        std::unique_ptr<Texture> t(new Texture("res/Textures/blue_circle.png"));
        textures.push_back(std::move(t));
        std::unique_ptr<Texture> t2(new Texture("res/Textures/pika.png"));
        textures.push_back(std::move(t2));
    }

    int tNum = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            SceneObject* so = scene.CreateSceneObject();
            so->SetPosition(x * 0.3f, y * 0.3f);
            so->AddRenderObject();
            so->renderObject->GenBuffers(data, 16, indexBufferData, 6);
            //so->renderObject->SetTexture(textures[tNum].get());
            so->renderObject->SetTexture(textures[0].get());
            so->renderObject->SetShader(shaders[0].get());
        }
    }
   
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glfwDestroyWindow(window);
    //glfwTerminate();

    return 0;
}

int main(void)
{
    return BoulderRun();
}