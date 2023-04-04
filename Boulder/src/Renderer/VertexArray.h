#pragma once

#include "VertexBuffer.h"

class VertexArray 
{
private:
	unsigned int boulder_vertexArrayID;
public:
	VertexArray();
	~VertexArray();

	void Gen(const VertexBuffer* vb);

	void Bind() const;
	void Unbind() const;
};