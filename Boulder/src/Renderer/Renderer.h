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

	std::vector<std::unique_ptr<RenderObject>> renderObjects;
	void UpdateProjectionMatrix();
public:
	Renderer(float windowWidth, float windowHeight);
	~Renderer();

	void Clear();
	void Draw();

	void SetViewMatrix(float x, float y);

	void UpdateWindowDimensions(float width, float height);
	void SetProjectionWidth(float width);

	inline glm::mat4* GetProjectionMatrix() { return &projectionMatrix; }
	inline glm::mat4* GetViewMatrix() { return &viewMatrix; }
	inline std::vector<std::unique_ptr<RenderObject>>* GetRenderObjects() { return &renderObjects; }
};