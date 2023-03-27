#include "RenderObject.h"

RenderObject::RenderObject(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount)
	:vb(vertexBufferData, vertexBufferCount), ib(indexBufferData, indexBufferCount), va(), shader()
{
}

RenderObject::~RenderObject()
{

}

void RenderObject::Bind() const
{
	shader.Bind();
	vb.Bind();
	ib.Bind();
	va.Bind();
}

void RenderObject::Unbind() const
{
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();
	va.Unbind();
}
