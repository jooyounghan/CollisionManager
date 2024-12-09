#include "pch.h"
#include "CollidableSphere.h"
#include "CollisionVisitor.h"

using namespace DirectX;

bool CollidableSphere::Accept(ICollisionVisitor& collisionVisitor) const
{
	return collisionVisitor.Visit(this);
}

DirectX::BoundingBox CollidableSphere::GetBoundingBox(const float& margin) const
{
	return DirectX::BoundingBox(Center, XMFLOAT3(Radius + margin, Radius + margin, Radius + margin));
}
