#pragma once
#include "CollisionVisitor.h"

class IntersectVisitor : public ACollisionVisitor
{
public:
	IntersectVisitor(const std::shared_ptr<ICollisionAcceptor>& collisionAcceptor);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox)const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};

class IntersectSphereVisitor : public ACollisionSpecifiedVisitor<CollidableSphere>
{
public:
	IntersectSphereVisitor(CollidableSphere* collidableSphere);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox) const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};

class IntersectOrientedBoxVisitor : public ACollisionSpecifiedVisitor<CollidableOrientedBox>
{
public:
	IntersectOrientedBoxVisitor(CollidableOrientedBox* collidableOrientedBox);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox) const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};


class IntersectFrustumVisitor : public ACollisionSpecifiedVisitor<CollidableFrustum>
{
public:
	IntersectFrustumVisitor(CollidableFrustum* collidableFrustum);

public:
	virtual bool Visit(CollidableSphere* collidableSphere) const override;
	virtual bool Visit(CollidableOrientedBox* collidableOrientedBox) const override;
	virtual bool Visit(CollidableFrustum* collidableFrustum) const override;
};
