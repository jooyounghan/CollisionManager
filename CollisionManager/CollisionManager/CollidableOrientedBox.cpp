#include "pch.h"
#include "CollidableOrientedBox.h"
#include "CollisionVisitor.h"

bool CollidableOrientedBox::Accept(ICollisionVisitor& collisionVisitor)
{
	return collisionVisitor.Visit(this);
}
