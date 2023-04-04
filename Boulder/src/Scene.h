#pragma once
#include "SceneObject.h"
#include "Renderer/Renderer.h"

#include <vector>
#include <memory>

class Scene
{
private:
	std::vector<std::unique_ptr<SceneObject>> sceneObjects;
public:
	Renderer* renderer;
	Scene(Renderer* renderer);
	~Scene();

	SceneObject* CreateSceneObject();

	inline std::vector<std::unique_ptr<SceneObject>>* GetSceneObjects() { return &sceneObjects; }
};