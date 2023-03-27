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
	Shader shader;
public:
	RenderObject(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount);
	~RenderObject();

	void Bind() const;
	void Unbind() const;

	//inline VertexArray* GetVertexArray() { return &va; }
	//inline VertexBuffer* GetVertexBuffer() { return &vb; }
	//inline IndexBuffer* GetIndexBuffer() { return &ib; }
	//inline Shader* GetShader() { return &shader; }
};