#pragma once

class VertexBuffer
{
private:
	unsigned int boulder_vertexBufferID;
public:
	VertexBuffer(const void* vertexBufferData, unsigned int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};