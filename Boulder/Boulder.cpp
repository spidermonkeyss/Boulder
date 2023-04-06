#pragma once
#include "src/Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Dependencies/rapidjson/document.h"

void LoadScene(std::string sceneFileName)
{
    std::ifstream myFile("res/Scenes/scene1.json");
    std::ostringstream tmp;
    tmp << myFile.rdbuf();
    const char* jsonStr = tmp.str().c_str();

    rapidjson::Document d;
    d.Parse(jsonStr);

    //rapidjson::Value& s = d["sceneName"];
    
    //s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    //StringBuffer buffer;
    //Writer<StringBuffer> writer(buffer);
    //d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    //std::cout << buffer.GetString() << std::endl;



    //Shaders
    Scene::loadedScene->renderer->LoadShader("Basic.shader");

    //Textures
    Scene::loadedScene->renderer->LoadTexture("blue_circle.png");
    Scene::loadedScene->renderer->LoadTexture("pika.png");

    //Objects
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            RenderObjectParameters rop;

            rop.position = Vector2(x * 0.3f, y * 0.3f);
            rop.bottomLeft = Vector2(-0.5f, -1.5f);
            rop.topRight = Vector2(0.5f, 0.5f);
            rop.shaderId = 0;
            rop.textureId = 1;

            Scene::loadedScene->CreateRenderObject(rop);
        }
    }
}

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

    LoadScene("scene1.json");

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