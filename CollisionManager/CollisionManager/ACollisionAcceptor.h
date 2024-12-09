#pragma once
#include <functional>
#include "DirectXMath/DirectXCollision.h"

class ICollisionVisitor;

class ACollisionAcceptor
{
public: 
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) const = 0;

public:
	virtual DirectX::BoundingBox GetBoundingBox(const float& margin) const = 0;

protected:
	std::function<void(const ACollisionAcceptor*)> OnUpdate
		= [](const ACollisionAcceptor*) {};

public:
	void SetUpdateHandler(const std::function<void(const ACollisionAcceptor*)>& onUpdate);

public:
	void Update();
};

