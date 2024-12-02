#include "pch.h"
#include "CollisionVisitor.h"

ACollisionVisitor::ACollisionVisitor(const std::shared_ptr<ICollisionAcceptor>& collisionAcceptor)
	: m_collisionAcceptor(collisionAcceptor)
{
}
