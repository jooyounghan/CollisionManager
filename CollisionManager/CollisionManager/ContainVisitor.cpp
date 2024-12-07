#include "pch.h"
#include "ContainVisitor.h"

using namespace std;
using namespace DirectX;


ContainVisitor::ContainVisitor(const shared_ptr<ACollisionAcceptor>& collisionAcceptor)
	: ACollisionVisitor(collisionAcceptor)
{
}

bool ContainVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	ContainSphereVisitor containSphereVisitor(collidableSphere);
	return m_collisionAcceptor->Accept(containSphereVisitor);
}

bool ContainVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	ContainOrientedBoxVisitor containOrientedBoxVisitor(collidableOrientedBox);
	return m_collisionAcceptor->Accept(containOrientedBoxVisitor);
}

bool ContainVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	ContainFrustumVisitor containFrustumVisitor(collidableFrustum);
	return m_collisionAcceptor->Accept(containFrustumVisitor);
}

ContainSphereVisitor::ContainSphereVisitor(const CollidableSphere* const collidableSphere)
	: ACollisionSpecifiedVisitor<CollidableSphere>(collidableSphere)
{
}

bool ContainSphereVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	return collidableSphere->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainSphereVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	return collidableOrientedBox->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainSphereVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	return collidableFrustum->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

ContainOrientedBoxVisitor::ContainOrientedBoxVisitor(const CollidableOrientedBox* const collidableOrientedBox)
	: ACollisionSpecifiedVisitor<CollidableOrientedBox>(collidableOrientedBox)
{
}

bool ContainOrientedBoxVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	return collidableSphere->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainOrientedBoxVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	return collidableOrientedBox->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainOrientedBoxVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	return collidableFrustum->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

ContainFrustumVisitor::ContainFrustumVisitor(const CollidableFrustum* const collidableFrustum)
	: ACollisionSpecifiedVisitor<CollidableFrustum>(collidableFrustum)
{
}

bool ContainFrustumVisitor::Visit(const CollidableSphere* const collidableSphere) const
{
	return collidableSphere->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainFrustumVisitor::Visit(const CollidableOrientedBox* const collidableOrientedBox) const
{
	return collidableOrientedBox->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainFrustumVisitor::Visit(const CollidableFrustum* const collidableFrustum) const
{
	return collidableFrustum->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}
