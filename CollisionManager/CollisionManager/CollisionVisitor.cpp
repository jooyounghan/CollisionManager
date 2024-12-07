#include "pch.h"
#include "CollisionVisitor.h"

using namespace std;

ACollisionVisitor::ACollisionVisitor(const shared_ptr<ACollisionAcceptor>& collisionAcceptor)
	: m_collisionAcceptor(collisionAcceptor)
{
}
