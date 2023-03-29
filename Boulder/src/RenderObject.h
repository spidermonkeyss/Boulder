#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class RenderObject
{
private:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	glm::mat4 transformMatrix;
public:
	RenderObject(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount);
	~RenderObject();

	void SetTransformPosition(float x, float y);

	void Bind() const;
	void Unbind() const;

	inline glm::mat4* GetTransformMatrix() { return &transformMatrix; }
};