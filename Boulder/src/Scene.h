#pragma once
#include "Renderer/Renderer.h"
#include "BoulderObject.h"

#include <vector>
#include <memory>

struct RenderObjectParameters
{
	Vector2 position;
	Vector2 bottomLeft;
	Vector2 topRight;
	unsigned int shaderId = 0;
	unsigned int textureId = 0;
};

class Scene
{
public:
	static Scene* loadedScene;

	Renderer* renderer;
	
	std::vector<std::unique_ptr<RenderObject>> renderObjects;
	
	std::vector<BoulderObject*> objects;

	Scene(Renderer* renderer);
	~Scene();

	RenderObject* CreateRenderObject(RenderObjectParameters rop);
};