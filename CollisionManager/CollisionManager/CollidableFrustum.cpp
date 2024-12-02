#include "pch.h"
#include "CollidableFrustum.h"
#include "CollisionVisitor.h"

bool CollidableFrustum::Accept(ICollisionVisitor& collisionVisitor)
{
	return collisionVisitor.Visit(this);
}
