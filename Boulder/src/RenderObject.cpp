#include "RenderObject.h"

RenderObject::RenderObject(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount)
{
	vb.Gen(vertexBufferData, vertexBufferCount);
	ib.Gen(indexBufferData, indexBufferCount);
	va.Gen(&vb);
}

RenderObject::~RenderObject()
{

}

void RenderObject::Bind() const
{
	vb.Bind();
	ib.Bind();
	va.Bind();
}

void RenderObject::Unbind() const
{
	vb.Unbind();
	ib.Unbind();
	va.Unbind();
}
