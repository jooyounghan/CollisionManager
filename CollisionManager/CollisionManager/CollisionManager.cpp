#include "pch.h"
#include "CollisionManager.h"
#include "IntersectVisitor.h"
#include "ContainVisitor.h"

using namespace std;

void CollisionManager::CheckAllCollision()
{
	for (const auto& collisionChannelNameToCollidables : m_collisionChannelNamesToCollidables)
	{
		const string collsionChannelName = collisionChannelNameToCollidables.first;
		const vector<shared_ptr<ICollisionAcceptor>> collidables = collisionChannelNameToCollidables.second;
		CheckCollisionHelper(collidables);
	}
}

void CollisionManager::CheckCollision(const string& channelName)
{
	if (m_collisionChannelNamesToCollidables.find(channelName) != m_collisionChannelNamesToCollidables.end())
	{
		const vector<shared_ptr<ICollisionAcceptor>>& collidables = m_collisionChannelNamesToCollidables[channelName];
		CheckCollisionHelper(collidables);
	}
}

void CollisionManager::CheckCollisionHelper(const vector<shared_ptr<ICollisionAcceptor>>& collidables)
{
	for (const shared_ptr<ICollisionAcceptor>& collidable1 : collidables)
	{
		IntersectVisitor intersectVisitor(collidable1);
		for (const shared_ptr<ICollisionAcceptor>& collidable2 : collidables)
		{
			if (collidable1 == collidable2) continue;

			if (collidable2->Accept(intersectVisitor))
			{
				const shared_ptr<ICollisionEventReceiver>& receiver1 = m_collidablesToRecievers[collidable1];
				const shared_ptr<ICollisionEventReceiver>& reciever2 = m_collidablesToRecievers[collidable2];

				if (receiver1 != nullptr) receiver1->Test();
				if (reciever2 != nullptr) reciever2->Test();
			}
		}
	}
}
