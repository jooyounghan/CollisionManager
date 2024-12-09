#include "pch.h"
#include "CollisionVisitor.h"

using namespace std;

ACollisionVisitor::ACollisionVisitor(ACollisionAcceptor* collisionAcceptor)
	: m_collisionAcceptor(collisionAcceptor)
{
}
