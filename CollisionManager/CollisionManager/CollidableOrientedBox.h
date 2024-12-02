#pragma once
#include "ICollisionAcceptor.h"

class CollidableOrientedBox : public ICollisionAcceptor, public DirectX::BoundingOrientedBox
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) override;
};

