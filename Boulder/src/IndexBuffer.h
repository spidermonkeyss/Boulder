#pragma once

class IndexBuffer
{
private:
	unsigned int boulder_indexBufferID;
public:
	IndexBuffer();
	~IndexBuffer();

	void Gen(const void* indexBufferData, unsigned int size);

	void Bind() const;
	void Unbind() const;
};