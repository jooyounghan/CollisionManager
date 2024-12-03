#include "pch.h"
#include "CollisionManager.h"
#include "IntersectVisitor.h"
#include "ContainVisitor.h"

#include <algorithm>

using namespace std;

void CollisionManager::CheckAllChannelCollision()
{
	for (const auto& channelNameToCollidables : m_channelNamesToCollidables)
	{
		CheckChannelCollisionHelper(channelNameToCollidables.second);
	}
}

void CollisionManager::CheckChannelCollision(const string& channelName)
{
	if (m_channelNamesToCollidables.find(channelName) != m_channelNamesToCollidables.end())
	{
		const vector<shared_ptr<ICollisionAcceptor>>& collidables = m_channelNamesToCollidables[channelName];
		CheckChannelCollisionHelper(collidables);
	}
}

void CollisionManager::RegisterCollidableForChannel(
	const string& channelName, 
	const shared_ptr<ICollisionAcceptor>& collidable, 
	const shared_ptr<ACollisionEventReceiver>& receiver
)
{
	m_channelNamesToCollidables[channelName].emplace_back(collidable);
	m_collidablesToRecievers[collidable] = receiver;
	m_recieversToCollidables[receiver] = collidable;
	receiver->OnDispose = [&](const shared_ptr<ACollisionEventReceiver>& receiver) { return DisposeEventReceiver(receiver); };
}

void CollisionManager::CheckAllRelationCollision()
{
	for (auto& relationNameToGroups : m_relationNamesToGroups)
	{
		CheckRelationCollisionHelper(relationNameToGroups.second);

	}
}

void CollisionManager::ChecRelationCollision(const string& relationName)
{
	if (m_relationNamesToGroups.find(relationName) != m_relationNamesToGroups.end())
	{
		const pair<vector<shared_ptr<ICollisionAcceptor>>, vector<shared_ptr<ICollisionAcceptor>>>& groups = m_relationNamesToGroups[relationName];
		CheckRelationCollisionHelper(groups);
	}
}

void CollisionManager::RegisterCheckerCollidableForRelation(
	const string& channelName, 
	const shared_ptr<ICollisionAcceptor>& collisionChecker, 
	const shared_ptr<ACollisionEventReceiver>& checkerReceiver
)
{
	pair<vector<shared_ptr<ICollisionAcceptor>>, vector<shared_ptr<ICollisionAcceptor>>>& groups = m_relationNamesToGroups[channelName];
	vector<shared_ptr<ICollisionAcceptor>>& collisionCheckers = groups.first;

	if (remove_if(collisionCheckers.begin(), collisionCheckers.end(), [&](const shared_ptr<ICollisionAcceptor>& collidable) { return collidable == collisionChecker; }) == collisionCheckers.end())
	{
		collisionCheckers.emplace_back(collisionChecker);
		m_collidablesToRecievers[collisionChecker] = checkerReceiver;
		m_recieversToCollidables[checkerReceiver] = collisionChecker;
		checkerReceiver->OnDispose = [&](const shared_ptr<ACollisionEventReceiver>& receiver) { return DisposeEventReceiver(receiver); };

	}

}

void CollisionManager::RegisterTargetCollidableForRelation(const string& channelName, const shared_ptr<ICollisionAcceptor>& collisionTarget, const shared_ptr<ACollisionEventReceiver>& targetReceiver)
{
	pair<vector<shared_ptr<ICollisionAcceptor>>, vector<shared_ptr<ICollisionAcceptor>>>& groups = m_relationNamesToGroups[channelName];
	vector<shared_ptr<ICollisionAcceptor>>& collisionTargets = groups.second;

	if (remove_if(collisionTargets.begin(), collisionTargets.end(), [&](const shared_ptr<ICollisionAcceptor>& collidable) { return collidable == collisionTarget; }) == collisionTargets.end())
	{
		collisionTargets.emplace_back(collisionTarget);
		m_collidablesToRecievers[collisionTarget] = targetReceiver;
		m_recieversToCollidables[targetReceiver] = collisionTarget;
		targetReceiver->OnDispose = [&](const shared_ptr<ACollisionEventReceiver>& receiver) { return DisposeEventReceiver(receiver); };

	}
}

void CollisionManager::DisposeEventReceiver(const shared_ptr<ACollisionEventReceiver>& receiver)
{
	if (m_recieversToCollidables.find(receiver) != m_recieversToCollidables.end())
	{
		const shared_ptr<ICollisionAcceptor>& disposedCollidable = m_recieversToCollidables[receiver];

		for (auto& collisionChannelNameToCollidables : m_channelNamesToCollidables)
		{
			const string& channelName = collisionChannelNameToCollidables.first;
			vector<shared_ptr<ICollisionAcceptor>>& collidables = collisionChannelNameToCollidables.second;

			if (remove_if(collidables.begin(), collidables.end(), [&](const shared_ptr<ICollisionAcceptor>& acceptor) {return acceptor == disposedCollidable; }) != collidables.end())
			{
				m_collidablesToRecievers.erase(disposedCollidable);
				m_recieversToCollidables.erase(receiver);
				return;
			}
		}
	}
}

void CollisionManager::CheckChannelCollisionHelper(const vector<shared_ptr<ICollisionAcceptor>>& collidables)
{
	for (size_t reference_idx = 0; reference_idx < collidables.size(); ++reference_idx)
	{
		const shared_ptr<ICollisionAcceptor>& collidable1 = collidables[reference_idx];
		IntersectVisitor intersectVisitor(collidable1);
		for (size_t target_idx = reference_idx + 1; target_idx < collidables.size(); ++target_idx)
		{
			const shared_ptr<ICollisionAcceptor>& collidable2 = collidables[target_idx];

			if (collidable2->Accept(intersectVisitor))
			{
				const shared_ptr<ACollisionEventReceiver>& receiver1 = m_collidablesToRecievers[collidable1];
				const shared_ptr<ACollisionEventReceiver>& reciever2 = m_collidablesToRecievers[collidable2];

				if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
				if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
			}
		}
	}
}

void CollisionManager::CheckRelationCollisionHelper(const pair<vector<shared_ptr<ICollisionAcceptor>>, vector<shared_ptr<ICollisionAcceptor>>>& groups)
{
	const vector<shared_ptr<ICollisionAcceptor>>& collisionCheckers = groups.first;
	const vector<shared_ptr<ICollisionAcceptor>>& collisionTargets = groups.second;

	for (const shared_ptr<ICollisionAcceptor>& collisionChecker : collisionCheckers)
	{
		IntersectVisitor intersectVisitor(collisionChecker);
		for (const shared_ptr<ICollisionAcceptor>& collisionTarget : collisionTargets)
		{
			if (collisionTarget->Accept(intersectVisitor))
			{
				const shared_ptr<ACollisionEventReceiver>& receiver1 = m_collidablesToRecievers[collisionChecker];
				const shared_ptr<ACollisionEventReceiver>& reciever2 = m_collidablesToRecievers[collisionTarget];

				if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
				if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
			}
		}
	}
}
