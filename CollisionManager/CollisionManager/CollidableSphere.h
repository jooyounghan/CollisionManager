#pragma once
#include "ICollisionAcceptor.h"

class CollidableSphere : public ICollisionAcceptor, public DirectX::BoundingSphere
{
public:
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) override;
};

