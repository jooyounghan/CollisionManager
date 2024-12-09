#include "pch.h"
#include "IntersectVisitor.h"

using namespace std;
using namespace DirectX;

IntersectVisitor::IntersectVisitor(ACollisionAcceptor* collisionAcceptor)
	: ACollisionVisitor(collisionAcceptor)
{
}

bool IntersectVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	IntersectSphereVisitor intersectSphereVisitor(collidableSphere);
	return m_collisionAcceptor->Accept(intersectSphereVisitor);
}

bool IntersectVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	IntersectOrientedBoxVisitor intersectOrientedBoxVisitor(collidableOrientedBox);
	return m_collisionAcceptor->Accept(intersectOrientedBoxVisitor);
}

bool IntersectVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	IntersectFrustumVisitor intersectFrustumVisitor(collidableFrustum);
	return m_collisionAcceptor->Accept(intersectFrustumVisitor);
}

IntersectSphereVisitor::IntersectSphereVisitor(const CollidableSphere* const collidableSphere)
	: ACollisionSpecifiedVisitor<CollidableSphere>(collidableSphere)
{

}

bool IntersectSphereVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	return collidableSphere->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectSphereVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	return collidableOrientedBox->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectSphereVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	return collidableFrustum->Intersects(*m_specifiedCollisionAccpetor);
}

IntersectOrientedBoxVisitor::IntersectOrientedBoxVisitor(const CollidableOrientedBox* const collidableOrientedBox)
	: ACollisionSpecifiedVisitor<CollidableOrientedBox>(collidableOrientedBox)
{
}

bool IntersectOrientedBoxVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	return collidableSphere->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectOrientedBoxVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	return collidableOrientedBox->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectOrientedBoxVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	return collidableFrustum->Intersects(*m_specifiedCollisionAccpetor);
}


IntersectFrustumVisitor::IntersectFrustumVisitor(const CollidableFrustum* const collidableFrustum)
	: ACollisionSpecifiedVisitor<CollidableFrustum>(collidableFrustum)
{
}

bool IntersectFrustumVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	return collidableSphere->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectFrustumVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	return collidableOrientedBox->Intersects(*m_specifiedCollisionAccpetor);
}

bool IntersectFrustumVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	return collidableFrustum->Intersects(*m_specifiedCollisionAccpetor);
}
