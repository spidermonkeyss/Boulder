#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class RenderObject
{
private:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	Texture* texture;
	Shader* shader;

	glm::mat4 transformMatrix;
public:
	RenderObject();
	RenderObject(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount);
	~RenderObject();

	void GenBuffers(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount);
	void SetMatrixPosition(float x, float y);
	void SetTexture(Texture* texture);
	void SetShader(Shader* shader);

	void Bind() const;
	void Unbind() const;

	inline glm::mat4* GetTransformMatrix() { return &transformMatrix; }
	inline Texture* GetTexture() { return texture; }
	inline Shader* GetShader() { return shader; }
};