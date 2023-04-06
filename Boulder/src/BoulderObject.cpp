#include "BoulderObject.h"

unsigned int BoulderObject::boulderObjectIdCount = 0;

BoulderObject::BoulderObject()
{
	name = "Unnamed";
	boulderObjectID = boulderObjectIdCount;
	boulderObjectIdCount++;
}

BoulderObject::~BoulderObject()
{
}

void BoulderObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
