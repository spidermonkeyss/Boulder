#include "SceneObject.h"
#include "Scene.h"

unsigned int SceneObject::sceneObjectIdCount = 0;

SceneObject::SceneObject(Scene* scene)
{
	sceneObjectID = sceneObjectIdCount;
	renderObject = nullptr;
	this->scene = scene;
	sceneObjectIdCount++;
}

SceneObject::~SceneObject()
{
}

void SceneObject::AddRenderObject()
{
	std::unique_ptr<RenderObject> ro(new RenderObject());
	ro->SetMatrixPosition(position.x, position.y);
	scene->renderer->GetRenderObjects()->push_back(std::move(ro));
	renderObject = scene->renderer->GetRenderObjects()->back().get();
}

void SceneObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	if (renderObject != nullptr)
		renderObject->SetMatrixPosition(x, y);
}
