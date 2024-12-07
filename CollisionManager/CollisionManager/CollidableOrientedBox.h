#pragma once
#include "ACollisionAcceptor.h"

class CollidableOrientedBox : public ACollisionAcceptor, public DirectX::BoundingOrientedBox
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) const override;

public:
	virtual bool IsInVolume(const DirectX::BoundingBox& volume) const override;
	virtual bool IsIntersectWithVolume(const DirectX::BoundingBox& volume) const override;
	virtual bool IsDisjointWithVolume(const DirectX::BoundingBox& volume) const override;
};

