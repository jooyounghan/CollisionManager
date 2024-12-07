#include "pch.h"
#include "CollidableSphere.h"
#include "CollisionVisitor.h"

using namespace DirectX;

bool CollidableSphere::Accept(ICollisionVisitor& collisionVisitor) const
{
	return collisionVisitor.Visit(this);
}

bool CollidableSphere::IsInVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::CONTAINS;
}

bool CollidableSphere::IsIntersectWithVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::INTERSECTS;
}

bool CollidableSphere::IsDisjointWithVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::DISJOINT;
}