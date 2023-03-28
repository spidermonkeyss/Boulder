#include "IndexBuffer.h"
#include "GLCall.h"

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &boulder_indexBufferID));
}

void IndexBuffer::Gen(const void* indexBufferData, unsigned int size)
{
	GLCall(glGenBuffers(1, &boulder_indexBufferID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boulder_indexBufferID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indexBufferData, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boulder_indexBufferID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
