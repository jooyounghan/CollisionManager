#pragma once
#include "ACollisionAcceptor.h"

class CollidableSphere : public ACollisionAcceptor, public DirectX::BoundingSphere
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) const override;

public:
	virtual DirectX::BoundingBox GetBoundingBox(const float& margin) const override;
};

