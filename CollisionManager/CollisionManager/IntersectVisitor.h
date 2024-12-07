#pragma once
#include "CollisionVisitor.h"

class IntersectVisitor : public ACollisionVisitor
{
public:
	IntersectVisitor(const std::shared_ptr<ACollisionAcceptor>& collisionAcceptor);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox)const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};

class IntersectSphereVisitor : public ACollisionSpecifiedVisitor<CollidableSphere>
{
public:
	IntersectSphereVisitor(const CollidableSphere* const collidableSphere);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox) const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};

class IntersectOrientedBoxVisitor : public ACollisionSpecifiedVisitor<CollidableOrientedBox>
{
public:
	IntersectOrientedBoxVisitor(const CollidableOrientedBox* const collidableOrientedBox);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox) const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};


class IntersectFrustumVisitor : public ACollisionSpecifiedVisitor<CollidableFrustum>
{
public:
	IntersectFrustumVisitor(const CollidableFrustum* const collidableFrustum);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox) const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};
