#pragma once
#include "../BoulderObject.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class RenderObject : public BoulderObject
{
private:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	Texture* texture;
	Shader* shader;

	glm::mat4 transformMatrix;

	void SetMatrixPosition(float x, float y);
public:
	RenderObject();
	~RenderObject();

	void GenBuffers(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount);
	void SetTexture(Texture* texture);
	void SetShader(Shader* shader);

	void SetPosition(float x, float y) override;


	void Bind() const;
	void Unbind() const;

	inline glm::mat4* GetTransformMatrix() { return &transformMatrix; }
	inline Texture* GetTexture() { return texture; }
	inline Shader* GetShader() { return shader; }
};