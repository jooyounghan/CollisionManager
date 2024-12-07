#include "pch.h"
#include "CollidableOrientedBox.h"
#include "CollisionVisitor.h"

using namespace DirectX;

bool CollidableOrientedBox::Accept(ICollisionVisitor& collisionVisitor) const
{
	return collisionVisitor.Visit(this);
}

bool CollidableOrientedBox::IsInVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::CONTAINS;
}

bool CollidableOrientedBox::IsIntersectWithVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::INTERSECTS;
}

bool CollidableOrientedBox::IsDisjointWithVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::DISJOINT;
}