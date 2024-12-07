#include "pch.h"
#include "CollidableFrustum.h"
#include "CollisionVisitor.h"

using namespace DirectX;

bool CollidableFrustum::Accept(ICollisionVisitor& collisionVisitor) const
{
	return collisionVisitor.Visit(this);
}

bool CollidableFrustum::IsInVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::CONTAINS;
}

bool CollidableFrustum::IsIntersectWithVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::INTERSECTS;
}

bool CollidableFrustum::IsDisjointWithVolume(const BoundingBox& volume) const
{
	return volume.Contains(*this) == ContainmentType::DISJOINT;
}
