#include "pch.h"
#include "ContainVisitor.h"

using namespace std;
using namespace DirectX;


ContainVisitor::ContainVisitor(const std::shared_ptr<ICollisionAcceptor>& collisionAcceptor)
	: ACollisionVisitor(collisionAcceptor)
{
}

bool ContainVisitor::Visit(CollidableSphere* collidableSphere) const
{
	ContainSphereVisitor containSphereVisitor(collidableSphere);
	return m_collisionAcceptor->Accept(containSphereVisitor);
}

bool ContainVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	ContainOrientedBoxVisitor containOrientedBoxVisitor(collidableOrientedBox);
	return m_collisionAcceptor->Accept(containOrientedBoxVisitor);
}

bool ContainVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	ContainFrustumVisitor containFrustumVisitor(collidableFrustum);
	return m_collisionAcceptor->Accept(containFrustumVisitor);
}

ContainSphereVisitor::ContainSphereVisitor(CollidableSphere* collidableSphere)
	: ACollisionSpecifiedVisitor<CollidableSphere>(collidableSphere)
{
}

bool ContainSphereVisitor::Visit(CollidableSphere* collidableSphere) const
{
	return collidableSphere->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainSphereVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	return collidableOrientedBox->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainSphereVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	return collidableFrustum->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

ContainOrientedBoxVisitor::ContainOrientedBoxVisitor(CollidableOrientedBox* collidableOrientedBox)
	: ACollisionSpecifiedVisitor<CollidableOrientedBox>(collidableOrientedBox)
{
}

bool ContainOrientedBoxVisitor::Visit(CollidableSphere* collidableSphere) const
{
	return collidableSphere->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainOrientedBoxVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	return collidableOrientedBox->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainOrientedBoxVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	return collidableFrustum->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

ContainFrustumVisitor::ContainFrustumVisitor(CollidableFrustum* collidableFrustum)
	: ACollisionSpecifiedVisitor<CollidableFrustum>(collidableFrustum)
{
}

bool ContainFrustumVisitor::Visit(CollidableSphere* collidableSphere) const
{
	return collidableSphere->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainFrustumVisitor::Visit(CollidableOrientedBox* collidableOrientedBox) const
{
	return collidableOrientedBox->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}

bool ContainFrustumVisitor::Visit(CollidableFrustum* collidableFrustum) const
{
	return collidableFrustum->Contains(*m_specifiedCollisionAccpetor) == ContainmentType::CONTAINS;
}
