#pragma once
#include "ACollisionAcceptor.h"

class CollidableOrientedBox : public ACollisionAcceptor, public DirectX::BoundingOrientedBox
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) const override;

public:
	virtual DirectX::BoundingBox GetBoundingBox(const float& margin) const override;
};

