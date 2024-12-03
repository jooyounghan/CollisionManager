#pragma once
#include <memory>
#include "DirectXMath/DirectXCollision.h"

class ICollisionVisitor;

class ICollisionAcceptor
{
public: 
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) = 0;
};

