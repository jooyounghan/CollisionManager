#pragma once
#include "CollisionVisitor.h"

class ContainVisitor : public ACollisionVisitor
{
public:
	ContainVisitor(const std::shared_ptr<ACollisionAcceptor>& collisionAcceptor);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox)const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};


class ContainSphereVisitor : public ACollisionSpecifiedVisitor<CollidableSphere>
{
public:
	ContainSphereVisitor(const CollidableSphere* const collidableSphere);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox) const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};

class ContainOrientedBoxVisitor : public ACollisionSpecifiedVisitor<CollidableOrientedBox>
{
public:
	ContainOrientedBoxVisitor(const CollidableOrientedBox* const collidableOrientedBox);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox) const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};


class ContainFrustumVisitor : public ACollisionSpecifiedVisitor<CollidableFrustum>
{
public:
	ContainFrustumVisitor(const CollidableFrustum* const collidableFrustum);

public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const override;
	virtual bool Visit(const CollidableOrientedBox* const collidableOrientedBox) const override;
	virtual bool Visit(const CollidableFrustum* const collidableFrustum) const override;
};
