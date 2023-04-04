#include "Scene.h"

Scene::Scene(Renderer* renderer)
{
	this->renderer = renderer;
}

Scene::~Scene()
{
}

SceneObject* Scene::CreateSceneObject()
{
    std::unique_ptr<SceneObject> sceneObject(new SceneObject(this));
    sceneObjects.push_back(std::move(sceneObject));
   
	return sceneObjects.back().get();
}
