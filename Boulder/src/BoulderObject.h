#pragma once
#include "Math/Vector2.h"

class Scene;

class BoulderObject
{
public:
	static unsigned int boulderObjectIdCount;

	unsigned int boulderObjectID;
	Vector2 position;
	std::string name;

	BoulderObject();
	~BoulderObject();

	virtual void SetPosition(float x, float y);

	inline Vector2 GetPosition() { return position; }
};