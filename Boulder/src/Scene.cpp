#include "Scene.h"

Scene* Scene::loadedScene = nullptr;

Scene::Scene(Renderer* renderer)
{
	this->renderer = renderer;
	Scene::loadedScene = this;
}

Scene::~Scene()
{
}

RenderObject* Scene::CreateRenderObject(RenderObjectParameters rop)
{
	unsigned int indexBufferData[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	float data[16] =
	{
		rop.bottomLeft.x, rop.bottomLeft.y, 0.0f, 0.0f,//Bot left
		rop.topRight.x,   rop.bottomLeft.y, 1.0f, 0.0f,//Bot right
		rop.topRight.x,   rop.topRight.y,	1.0f, 1.0f,//Top right
		rop.bottomLeft.x, rop.topRight.y,	0.0f, 1.0f //Top left
	};

	std::unique_ptr<RenderObject> ro(new RenderObject());
	ro->SetPosition(rop.position.x, rop.position.y);
	ro->GenBuffers(data, 16, indexBufferData, 6);
	ro->SetShader(Scene::loadedScene->renderer->shaders[rop.shaderId].get());
	ro->SetTexture(Scene::loadedScene->renderer->textures[rop.textureId].get());

	renderObjects.push_back(std::move(ro));

	objects.push_back((BoulderObject*)(renderObjects.back().get()));

	return renderObjects.back().get();
}
