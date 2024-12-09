#include "pch.h"
#include "CollisionManager.h"
#include "IntersectVisitor.h"
#include "ContainVisitor.h"

#include <algorithm>

using namespace std;
using namespace DirectX;

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
		const vector<ACollisionAcceptor*>& collidables = m_channelNamesToCollidables[channelName];
		CheckChannelCollisionHelper(collidables);
	}
}

void CollisionManager::RegisterCollidableForChannel(
	const string& channelName, 
	ACollisionAcceptor* const collidable, 
	ACollisionEventReceiver* const receiver
)
{
	m_channelNamesToCollidables[channelName].emplace_back(collidable);
	m_collidablesToRecievers[collidable] = receiver;
	m_recieversToCollidables[receiver] = collidable;
	receiver->SetDisposeHandler([&](ACollisionEventReceiver* receiver) { return DisposeEventReceiver(receiver); });
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
		const pair<vector<ACollisionAcceptor*>, vector<ACollisionAcceptor*>>& groups = m_relationNamesToGroups[relationName];
		CheckRelationCollisionHelper(groups);
	}
}

void CollisionManager::RegisterCheckerCollidableForRelation(
	const string& channelName, 
	ACollisionAcceptor* const collisionChecker,
	ACollisionEventReceiver* const checkerReceiver
)
{
	pair<vector<ACollisionAcceptor*>, vector<ACollisionAcceptor*>>& groups = m_relationNamesToGroups[channelName];
	vector<ACollisionAcceptor*>& collisionCheckers = groups.first;

	collisionCheckers.emplace_back(collisionChecker);
	m_collidablesToRecievers[collisionChecker] = checkerReceiver;
	m_recieversToCollidables[checkerReceiver] = collisionChecker;
	checkerReceiver->SetDisposeHandler([&](ACollisionEventReceiver* receiver) { return DisposeEventReceiver(receiver); });
}

void CollisionManager::RegisterTargetCollidableForRelation(
	const string& channelName, 
	ACollisionAcceptor* const collisionTarget,
	ACollisionEventReceiver* const targetReceiver
)
{
	pair<vector<ACollisionAcceptor*>, vector<ACollisionAcceptor*>>& groups = m_relationNamesToGroups[channelName];
	vector<ACollisionAcceptor*>& collisionTargets = groups.second;

	collisionTargets.emplace_back(collisionTarget);
	m_collidablesToRecievers[collisionTarget] = targetReceiver;
	m_recieversToCollidables[targetReceiver] = collisionTarget;
	targetReceiver->SetDisposeHandler([&](ACollisionEventReceiver* receiver) { return DisposeEventReceiver(receiver); });
}

void CollisionManager::DisposeEventReceiver(ACollisionEventReceiver* const receiver)
{
	if (m_recieversToCollidables.find(receiver) != m_recieversToCollidables.end())
	{
		ACollisionAcceptor* const disposedCollidable = m_recieversToCollidables[receiver];

		for (auto& collisionChannelNameToCollidables : m_channelNamesToCollidables)
		{
			vector<ACollisionAcceptor*>& collidables = collisionChannelNameToCollidables.second;
			RemoveHelper(collidables, disposedCollidable);
		}

		for (auto& collisionRelationNameToCollidablePairs : m_relationNamesToGroups)
		{
			vector<ACollisionAcceptor*>& collidableCheckers = collisionRelationNameToCollidablePairs.second.first;
			vector<ACollisionAcceptor*>& collidableTargets = collisionRelationNameToCollidablePairs.second.second;
			RemoveHelper(collidableCheckers, disposedCollidable);
			RemoveHelper(collidableTargets, disposedCollidable);
		}

		m_collidablesToRecievers.erase(disposedCollidable);
		m_recieversToCollidables.erase(receiver);
	}
}

void CollisionManager::CheckChannelCollisionHelper(const vector<ACollisionAcceptor*>& collidables)
{

	for (size_t reference_idx = 0; reference_idx < collidables.size(); ++reference_idx)
	{
		ACollisionAcceptor* collidable1 = collidables[reference_idx];
		ACollisionEventReceiver* receiver1 = m_collidablesToRecievers[collidable1];

		IntersectVisitor intersectVisitor(collidable1);
		for (size_t target_idx = reference_idx + 1; target_idx < collidables.size(); ++target_idx)
		{
			ACollisionAcceptor* collidable2 = collidables[target_idx];

			if (collidable2->Accept(intersectVisitor))
			{

				ACollisionEventReceiver* reciever2 = m_collidablesToRecievers[collidable2];

				if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
				if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
			}
		}
	}
}

void CollisionManager::CheckRelationCollisionHelper(const pair<vector<ACollisionAcceptor*>, vector<ACollisionAcceptor*>>& groups)
{
	const vector<ACollisionAcceptor*>& collisionCheckers = groups.first;
	const vector<ACollisionAcceptor*>& collisionTargets = groups.second;

	for (ACollisionAcceptor* collisionChecker : collisionCheckers)
	{
		ACollisionEventReceiver* receiver1 = m_collidablesToRecievers[collisionChecker];

		IntersectVisitor intersectVisitor(collisionChecker);
		for (ACollisionAcceptor* collisionTarget : collisionTargets)
		{
			if (collisionTarget->Accept(intersectVisitor))
			{
				ACollisionEventReceiver* reciever2 = m_collidablesToRecievers[collisionTarget];

				if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
				if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
			}
		}
	}
}

void CollisionManager::RemoveHelper(vector<ACollisionAcceptor*>& container, const ACollisionAcceptor* const target)
{
	container.erase(
		remove_if(
			container.begin(),
			container.end(),
			[&](const ACollisionAcceptor* const  acceptor) {return acceptor == target; }
		),
		container.end()
	);
}
