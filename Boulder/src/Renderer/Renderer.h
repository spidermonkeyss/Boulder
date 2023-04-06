#pragma once
#include "GLCall.h"
#include "RenderObject.h"

#include "../../Dependencies/glm/glm/gtc/matrix_transform.hpp"

#include <vector>

class Renderer
{
private:
	float windowWidth;
	float windowHeight;
	float aspectRatio;
	float projWidth;
	float projHeight;
	glm::mat4 projectionMatrix;

	glm::mat4 viewMatrix;

	void UpdateProjectionMatrix();
public:
	std::vector<std::unique_ptr<Shader>> shaders;
	std::vector<std::unique_ptr<Texture>> textures;

	Renderer(float windowWidth, float windowHeight);
	~Renderer();

	void Clear();
	void Draw();

	void LoadShader(std::string shaderFileName);
	void LoadTexture(std::string textureFileName);

	void SetViewMatrix(float x, float y);
	void SetProjectionWidth(float width);
	void UpdateWindowDimensions(float width, float height);

	inline glm::mat4* GetProjectionMatrix() { return &projectionMatrix; }
	inline glm::mat4* GetViewMatrix() { return &viewMatrix; }
};