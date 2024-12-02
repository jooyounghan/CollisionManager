#pragma once
#include "ICollisionAcceptor.h"

class CollidableFrustum : public ICollisionAcceptor, public DirectX::BoundingFrustum
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) override;
};

