#pragma once

class VertexBuffer
{
private:
	unsigned int boulder_vertexBufferID;
public:
	VertexBuffer();
	~VertexBuffer();

	void Gen(const void* vertexBufferData, unsigned int count);

	void Bind() const;
	void Unbind() const;
};