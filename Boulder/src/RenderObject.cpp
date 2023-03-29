#include "RenderObject.h"
#include "../Dependencies/glm/glm/gtc/matrix_transform.hpp"


RenderObject::RenderObject(const void* vertexBufferData, unsigned int vertexBufferCount, const void* indexBufferData, unsigned int indexBufferCount)
{
	vb.Gen(vertexBufferData, vertexBufferCount);
	ib.Gen(indexBufferData, indexBufferCount);
	va.Gen(&vb);

	transformMatrix = glm::mat4(1.0f);
}

RenderObject::~RenderObject()
{

}

void RenderObject::SetTransformPosition(float x, float y)
{
	transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
	/*
	glm::mat4 positionMat4 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
	glm::mat4 scaleMat4 = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));

	//YXZ Gimbol
	glm::mat4 rotationMat4 = glm::mat4(1.0f);
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	transformMatrix = positionMat4 * rotationMat4 * scaleMat4;
	*/
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
