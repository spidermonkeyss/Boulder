#include "Renderer.h"

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
    for (int i = 0; i < renderObjects.size(); i++)
    {
        renderObjects[i]->Bind();

        renderObjects[i]->GetShader()->SetUniformMat4f("u_v", viewMatrix);
        renderObjects[i]->GetShader()->SetUniformMat4f("u_p", projectionMatrix);

        renderObjects[i]->GetShader()->SetUniformMat4f("u_m", *renderObjects[i]->GetTransformMatrix());
        renderObjects[i]->GetShader()->SetUniform1i("u_Texture", 0);

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
