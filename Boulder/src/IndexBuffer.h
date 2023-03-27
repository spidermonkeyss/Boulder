#pragma once

class IndexBuffer
{
private:
	unsigned int boulder_indexBufferID;
public:
	IndexBuffer(const void* indexBufferData, unsigned int size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};