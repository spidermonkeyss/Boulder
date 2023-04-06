#include "Renderer.h"
#include "../Scene.h"

Renderer::Renderer(float windowWidth, float windowHeight)
{
    UpdateWindowDimensions(windowWidth, windowHeight);
    SetViewMatrix(0, 0);
    SetProjectionWidth(5.0f);
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.14f, 0.5f, 0.85f, 1.0f));
}

void Renderer::Draw()
{
    for (int i = 0; i < Scene::loadedScene->renderObjects.size(); i++)
    {
        Scene::loadedScene->renderObjects[i]->Bind();

        Scene::loadedScene->renderObjects[i]->GetShader()->SetUniformMat4f("u_v", viewMatrix);
        Scene::loadedScene->renderObjects[i]->GetShader()->SetUniformMat4f("u_p", projectionMatrix);

        Scene::loadedScene->renderObjects[i]->GetShader()->SetUniformMat4f("u_m", *Scene::loadedScene->renderObjects[i]->GetTransformMatrix());
        Scene::loadedScene->renderObjects[i]->GetShader()->SetUniform1i("u_Texture", 0);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    }
}

void Renderer::SetViewMatrix(float x, float y)
{
    viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
}

void Renderer::UpdateWindowDimensions(float width, float height)
{
    windowWidth = width;
    windowHeight = height;
    UpdateProjectionMatrix();
}

void Renderer::LoadShader(std::string shaderFileName)
{
    std::unique_ptr<Shader> s(new Shader("res/Shaders/" + shaderFileName, false));
    shaders.push_back(std::move(s));
}

void Renderer::LoadTexture(std::string textureFileName)
{
    std::unique_ptr<Texture> t(new Texture("res/Textures/" + textureFileName));
    textures.push_back(std::move(t));
}

void Renderer::SetProjectionWidth(float width)
{
    projWidth = width;
    UpdateProjectionMatrix();
}

void Renderer::UpdateProjectionMatrix()
{
    aspectRatio = (float)windowWidth / (float)windowHeight;
    projHeight = projWidth / aspectRatio;
    projectionMatrix = glm::ortho(-projWidth / 2, projWidth / 2, -projHeight / 2, projHeight / 2, -1.0f, 1.0f);
}
