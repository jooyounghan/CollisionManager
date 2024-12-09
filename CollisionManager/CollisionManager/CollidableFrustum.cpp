#include "pch.h"
#include "CollidableFrustum.h"
#include "CollisionVisitor.h"

using namespace DirectX;

bool CollidableFrustum::Accept(ICollisionVisitor& collisionVisitor) const
{
	return collisionVisitor.Visit(this);
}

DirectX::BoundingBox CollidableFrustum::GetBoundingBox(const float& margin) const
{
    XMFLOAT3 corners[8];
    GetCorners(corners);

    XMFLOAT3 minCorner = corners[0];
    XMFLOAT3 maxCorner = corners[0];

    for (int i = 1; i < 8; ++i)
    {
        minCorner.x = std::min(minCorner.x, corners[i].x);
        minCorner.y = std::min(minCorner.y, corners[i].y);
        minCorner.z = std::min(minCorner.z, corners[i].z);

        maxCorner.x = std::max(maxCorner.x, corners[i].x);
        maxCorner.y = std::max(maxCorner.y, corners[i].y);
        maxCorner.z = std::max(maxCorner.z, corners[i].z);
    }

    minCorner.x -= margin;
    minCorner.y -= margin;
    minCorner.z -= margin;

    maxCorner.x += margin;
    maxCorner.y += margin;
    maxCorner.z += margin;

    BoundingBox result;
    BoundingBox::CreateFromPoints(result, XMLoadFloat3(&minCorner), XMLoadFloat3(&maxCorner));
    return result;
}
