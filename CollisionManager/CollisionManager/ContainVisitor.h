#pragma once
#include "CollisionVisitor.h"

class ContainVisitor : public ACollisionVisitor
{
public:
	ContainVisitor(const std::shared_ptr<ICollisionAcceptor>& collisionAcceptor);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox)const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};


class ContainSphereVisitor : public ACollisionSpecifiedVisitor<CollidableSphere>
{
public:
	ContainSphereVisitor(CollidableSphere* collidableSphere);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox) const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};

class ContainOrientedBoxVisitor : public ACollisionSpecifiedVisitor<CollidableOrientedBox>
{
public:
	ContainOrientedBoxVisitor(CollidableOrientedBox* collidableOrientedBox);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox) const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};


class ContainFrustumVisitor : public ACollisionSpecifiedVisitor<CollidableFrustum>
{
public:
	ContainFrustumVisitor(CollidableFrustum* collidableFrustum);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox) const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};
