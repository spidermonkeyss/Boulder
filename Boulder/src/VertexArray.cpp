#include "VertexArray.h"
#include "GLCall.h"

VertexArray::VertexArray()
{
	//Vertex Array
	GLCall(glGenVertexArrays(1, &boulder_vertexArrayID));
	GLCall(glBindVertexArray(boulder_vertexArrayID));

	unsigned int offset = 0;
	unsigned int count = 2;
	unsigned int type = GL_FLOAT;
	unsigned int isNormalised = GL_FALSE;
	unsigned int stride = 0;

	//Position Arrtibute
	GLCall(glEnableVertexAttribArray(0));
	glVertexAttribPointer(0, count, type, isNormalised, stride, (const void*)offset);

	//offset += 2 * GL_FLOAT;
	//UV Arrtubute
	//GLCall(glEnableVertexAttribArray(1));
	//glVertexAttribPointer(1, count, type, isNormalised, stride, (const void*)offset);

	Unbind();
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &boulder_vertexArrayID));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(boulder_vertexArrayID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}