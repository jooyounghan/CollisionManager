#pragma once
#include <memory>

class ICollisionVisitor;

class ICollisionAcceptor
{
public: 
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) = 0;
};

