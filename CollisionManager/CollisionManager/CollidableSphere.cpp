#include "pch.h"
#include "CollidableSphere.h"
#include "CollisionVisitor.h"

bool CollidableSphere::Accept(ICollisionVisitor& collisionVisitor)
{
	return collisionVisitor.Visit(this);
}
