#pragma once
#include "src/Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Dependencies/rapidjson/document.h"

void LoadScene(std::string sceneFileName)
{
    std::cout << "Begin scene file load: " << sceneFileName << std::endl;

    //Shaders
    Scene::loadedScene->renderer->LoadShader("Basic.shader");

    //Textures
    Scene::loadedScene->renderer->LoadTexture("blue_circle.png");
    Scene::loadedScene->renderer->LoadTexture("pika.png");

    using namespace rapidjson;

    std::ifstream jsonFile("res/Scenes/" + sceneFileName);
    std::stringstream ss;
    ss << jsonFile.rdbuf();
    std::string jsonStr = ss.str();//The stringstream needs to be copied to a new string otherwise the char pointer will point to an empty string
    const char* jsonCStr = jsonStr.c_str();

    Document document;
    document.Parse(jsonCStr);

    //std::string errorMessage = "";
    std::vector<std::string> errorMessages;
    if (document.IsObject())
    {
        if (document.HasMember("sceneName"))
        {
            if (document["sceneName"].IsString())
                std::string s = document["sceneName"].GetString();
            else
                errorMessages.push_back("sceneName is not a string");
        }
        else
            errorMessages.push_back("Missing sceneName");

        if (document.HasMember("renderObjects"))
        {
            const Value& renderObjectsArray = document["renderObjects"];
            if (renderObjectsArray.IsArray())
            {
                std::cout << renderObjectsArray.Size() << " renderObjects from scene file" << std::endl;
                for (rapidjson::SizeType i = 0; i < renderObjectsArray.Size(); i++)
                {
                    const Value& renderObject = renderObjectsArray[i];
                    if (renderObject.IsObject())
                    {
                        RenderObjectParameters rop;
                        if (renderObject.HasMember("name"))
                        {
                            if (renderObject["name"].IsString())
                                rop.name = renderObject["name"].GetString();
                            else
                                errorMessages.push_back("renderObject " + std::to_string(i) + " name is not a string");
                        }
                        else
                            errorMessages.push_back("renderObject " + std::to_string(i) + " is missing name");

                        if (renderObject.HasMember("position"))
                        {
                            if (renderObject["position"].IsArray())
                            {
                                if (renderObject["position"][0].IsFloat())
                                    rop.position.x = renderObject["position"][0].GetFloat();
                                else
                                    errorMessages.push_back("renderObject " + std::to_string(i) + " position x is not a float");

                                if (renderObject["position"][0].IsFloat())
                                    rop.position.y = renderObject["position"][1].GetFloat();
                                else
                                    errorMessages.push_back("renderObject " + std::to_string(i) + " position y is not a float");
                            }
                            else
                                errorMessages.push_back("renderObject " + std::to_string(i) + " position is not an array");
                        }
                        else
                            errorMessages.push_back("renderObject " + std::to_string(i) + " is missing position");

                        if (renderObject.HasMember("bottomLeft"))
                        {
                            if (renderObject["bottomLeft"].IsArray())
                            {
                                if (renderObject["bottomLeft"][0].IsFloat())
                                    rop.bottomLeft.x = renderObject["bottomLeft"][0].GetFloat();
                                else
                                    errorMessages.push_back("renderObject " + std::to_string(i) + " bottomLeft x is not a float");

                                if (renderObject["bottomLeft"][0].IsFloat())
                                    rop.bottomLeft.y = renderObject["bottomLeft"][1].GetFloat();
                                else
                                    errorMessages.push_back("renderObject " + std::to_string(i) + " bottomLeft y is not a float");
                            }
                            else
                                errorMessages.push_back("renderObject " + std::to_string(i) + " bottomLeft is not an array");
                        }
                        else
                            errorMessages.push_back("renderObject " + std::to_string(i) + " is missing bottomLeft");

                        if (renderObject.HasMember("topRight"))
                        {
                            if (renderObject["topRight"].IsArray())
                            {
                                if (renderObject["topRight"][0].IsFloat())
                                    rop.topRight.x = renderObject["topRight"][0].GetFloat();
                                else
                                    errorMessages.push_back("renderObject " + std::to_string(i) + " topRight x is not a float");

                                if (renderObject["topRight"][0].IsFloat())
                                    rop.topRight.y = renderObject["topRight"][1].GetFloat();
                                else
                                    errorMessages.push_back("renderObject " + std::to_string(i) + " topRight y is not a float");
                            }
                            else
                                errorMessages.push_back("renderObject " + std::to_string(i) + " topRight is not an array");
                        }
                        else
                            errorMessages.push_back("renderObject " + std::to_string(i) + " is missing bottomLeft");

                        if (renderObject.HasMember("shaderId"))
                        {
                            if (renderObject["shaderId"].IsInt())
                                rop.shaderId = renderObject["shaderId"].GetInt();
                            else
                                errorMessages.push_back("renderObject " + std::to_string(i) + " shaderId is not an int");
                        }
                        else
                            errorMessages.push_back("renderObject " + std::to_string(i) + " is missing shaderId");

                        if (renderObject.HasMember("textureId"))
                        {
                            if (renderObject["textureId"].IsInt())
                                rop.textureId = renderObject["textureId"].GetInt();
                            else
                                errorMessages.push_back("renderObject " + std::to_string(i) + " textureId is not an int");
                        }
                        else
                            errorMessages.push_back("renderObject " + std::to_string(i) + " is missing shaderId");

                        Scene::loadedScene->CreateRenderObject(rop);
                    }
                    else
                        errorMessages.push_back("renderObject " + std::to_string(i) + " is not a object");
                }
            }
            else
                errorMessages.push_back("renderObjects is not an array");
        }
        else
            errorMessages.push_back("Missing renderObjects");
    }
    else
        errorMessages.push_back("could not parse");
    
    if (errorMessages.size() > 0)
    {
        for (int i = 0; i < errorMessages.size(); i++)
            std::cout << "Scene file error for " << sceneFileName << ": " << errorMessages[i] << std::endl;
        return;
    }

    std::cout << "Scene file loaded" << std::endl;
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