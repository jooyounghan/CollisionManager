#pragma once
#include "ACollisionAcceptor.h"

class CollidableFrustum : public ACollisionAcceptor, public DirectX::BoundingFrustum
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) const override;

public:
	virtual DirectX::BoundingBox GetBoundingBox(const float& margin) const override;
};

