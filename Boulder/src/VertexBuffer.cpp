#include "VertexBuffer.h"
#include "GLCall.h"

VertexBuffer::VertexBuffer()
{
	
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &boulder_vertexBufferID));
}

void VertexBuffer::Gen(const void* vertexBufferData, unsigned int count)
{
	GLCall(glGenBuffers(1, &boulder_vertexBufferID));//This generated a buffer of memory
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, boulder_vertexBufferID));//Will set the targets current buffer to be this
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertexBufferData, GL_STATIC_DRAW));//Fills the current bound buffer with data
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, boulder_vertexBufferID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
