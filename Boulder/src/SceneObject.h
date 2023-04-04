#pragma once
#include "Math/Vector2.h"
#include "Renderer/RenderObject.h"

class Scene;

class SceneObject
{
private:
	static unsigned int sceneObjectIdCount;
	Vector2 position;
public:
	Scene* scene;
	RenderObject* renderObject;

	unsigned int sceneObjectID;

	SceneObject(Scene* scene);
	~SceneObject();

	void AddRenderObject();
	void SetPosition(float x, float y);

	inline Vector2 GetPosition() { return position; }
};