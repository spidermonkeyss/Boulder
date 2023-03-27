#pragma once

class VertexArray 
{
private:
	unsigned int boulder_vertexArrayID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
};