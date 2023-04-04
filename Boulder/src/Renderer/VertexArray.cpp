#include "VertexArray.h"
#include "GLCall.h"

VertexArray::VertexArray()
{
	
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &boulder_vertexArrayID));
}

void VertexArray::Gen(const VertexBuffer* vb)
{
	vb->Bind();

	//Vertex Array
	GLCall(glGenVertexArrays(1, &boulder_vertexArrayID));
	GLCall(glBindVertexArray(boulder_vertexArrayID));

	unsigned int offset = 0;
	unsigned int positionCount = 2;
	unsigned int uvCount = 2;
	unsigned int type = GL_FLOAT;
	unsigned int isNormalised = GL_FALSE;
	unsigned int sizeOfFloat = 4;
	unsigned int stride = (positionCount + uvCount) * sizeOfFloat;

	//Position Arrtibute
	GLCall(glEnableVertexAttribArray(0));
	glVertexAttribPointer(0, positionCount, type, isNormalised, stride, (const void*)offset);

	offset += positionCount * sizeOfFloat;
	//UV Arrtubute
	GLCall(glEnableVertexAttribArray(1));
	glVertexAttribPointer(1, uvCount, type, isNormalised, stride, (const void*)offset);
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(boulder_vertexArrayID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}