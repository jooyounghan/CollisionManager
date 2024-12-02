#include "pch.h"
#include "IntersectVisitor.h"

using namespace DirectX;

IntersectVisitor::IntersectVisitor(const std::shared_ptr<ICollisionAcceptor>& collisionAcceptor)
	: ACollisionVisitor(collisionAcceptor)
{
}

bool IntersectVisitor::Visit(CollidableSphere* collidableSphere) const
{
	IntersectSphereVisitor intersectSphereVisitor(collidableSphere);
	return m_collisionAcceptor->Accept(intersectSphereVisitor);
}

bool IntersectVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	IntersectOrientedBoxVisitor intersectOrientedBoxVisitor(collidableOrientedBox);
	return m_collisionAcceptor->Accept(intersectOrientedBoxVisitor);
}

bool IntersectVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	IntersectFrustumVisitor intersectFrustumVisitor(collidableFrustum);
	return m_collisionAcceptor->Accept(intersectFrustumVisitor);
}

IntersectSphereVisitor::IntersectSphereVisitor(CollidableSphere* collidableSphere)
	: ACollisionSpecifiedVisitor<CollidableSphere>(collidableSphere)
{

}

bool IntersectSphereVisitor::Visit(CollidableSphere* collidableSphere) const
{
	return collidableSphere->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectSphereVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	return collidableOrientedBox->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectSphereVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	return collidableFrustum->Intersects(*m_specifiedCollisionAccpetor);
}

IntersectOrientedBoxVisitor::IntersectOrientedBoxVisitor(CollidableOrientedBox* collidableOrientedBox)
	: ACollisionSpecifiedVisitor<CollidableOrientedBox>(collidableOrientedBox)
{
}

bool IntersectOrientedBoxVisitor::Visit(CollidableSphere* collidableSphere) const
{
	return collidableSphere->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectOrientedBoxVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	return collidableOrientedBox->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectOrientedBoxVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	return collidableFrustum->Intersects(*m_specifiedCollisionAccpetor);
}


IntersectFrustumVisitor::IntersectFrustumVisitor(CollidableFrustum* collidableFrustum)
	: ACollisionSpecifiedVisitor<CollidableFrustum>(collidableFrustum)
{
}

bool IntersectFrustumVisitor::Visit(CollidableSphere* collidableSphere) const
{
	return collidableSphere->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectFrustumVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	return collidableOrientedBox->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectFrustumVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	return collidableFrustum->Intersects(*m_specifiedCollisionAccpetor);
}
