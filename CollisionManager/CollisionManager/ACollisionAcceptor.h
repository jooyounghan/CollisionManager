#pragma once
#include <memory>
#include <functional>
#include "DirectXMath/DirectXCollision.h"

class ICollisionVisitor;

class ACollisionAcceptor : public std::enable_shared_from_this<ACollisionAcceptor>
{
public: 
	virtual bool Accept(
		ICollisionVisitor& collisionVisitor
	) const = 0;

public:
	virtual bool IsInVolume(const DirectX::BoundingBox& volume) const = 0;
	virtual bool IsIntersectWithVolume(const DirectX::BoundingBox& volume) const = 0;
	virtual bool IsDisjointWithVolume(const DirectX::BoundingBox& volume) const = 0;

public:
	std::function<void(const std::shared_ptr<ACollisionAcceptor>&)> OnUpdate
		= [](const std::shared_ptr<ACollisionAcceptor>&) {};
};

