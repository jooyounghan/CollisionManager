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
		const vector<shared_ptr<ACollisionAcceptor>>& collidables = m_channelNamesToCollidables[channelName];
		CheckChannelCollisionHelper(collidables);
	}
}

void CollisionManager::RegisterCollidableForChannel(
	const string& channelName, 
	const shared_ptr<ACollisionAcceptor>& collidable, 
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
		const pair<vector<shared_ptr<ACollisionAcceptor>>, vector<shared_ptr<ACollisionAcceptor>>>& groups = m_relationNamesToGroups[relationName];
		CheckRelationCollisionHelper(groups);
	}
}

void CollisionManager::RegisterCheckerCollidableForRelation(
	const string& channelName, 
	const shared_ptr<ACollisionAcceptor>& collisionChecker, 
	const shared_ptr<ACollisionEventReceiver>& checkerReceiver
)
{
	pair<vector<shared_ptr<ACollisionAcceptor>>, vector<shared_ptr<ACollisionAcceptor>>>& groups = m_relationNamesToGroups[channelName];
	vector<shared_ptr<ACollisionAcceptor>>& collisionCheckers = groups.first;

	collisionCheckers.emplace_back(collisionChecker);
	m_collidablesToRecievers[collisionChecker] = checkerReceiver;
	m_recieversToCollidables[checkerReceiver] = collisionChecker;
	checkerReceiver->OnDispose = [&](const shared_ptr<ACollisionEventReceiver>& receiver) { return DisposeEventReceiver(receiver); };
}

void CollisionManager::RegisterTargetCollidableForRelation(const string& channelName, const shared_ptr<ACollisionAcceptor>& collisionTarget, const shared_ptr<ACollisionEventReceiver>& targetReceiver)
{
	pair<vector<shared_ptr<ACollisionAcceptor>>, vector<shared_ptr<ACollisionAcceptor>>>& groups = m_relationNamesToGroups[channelName];
	vector<shared_ptr<ACollisionAcceptor>>& collisionTargets = groups.second;

	collisionTargets.emplace_back(collisionTarget);
	m_collidablesToRecievers[collisionTarget] = targetReceiver;
	m_recieversToCollidables[targetReceiver] = collisionTarget;
	targetReceiver->OnDispose = [&](const shared_ptr<ACollisionEventReceiver>& receiver) { return DisposeEventReceiver(receiver); };
}

void CollisionManager::RegisterOctreeChecker(
	const string& volumeName, 
	const BoundingBox& collisionVolume, 
	const size_t& maxCollidablesCountPerNode
)
{
	m_volumeNameToOctree.emplace(volumeName, OctreeChecker(collisionVolume, maxCollidablesCountPerNode));
}

void CollisionManager::RegisterCollidableToOctree(
	const string& volumeName, 
	const shared_ptr<ACollisionAcceptor>& collidable, 
	const shared_ptr<ACollisionEventReceiver>& receiver
)
{
	if (m_volumeNameToOctree.find(volumeName) != m_volumeNameToOctree.end())
	{
		OctreeChecker& octreeChecker = m_volumeNameToOctree[volumeName];
		octreeChecker.InsertCollidable(collidable);

		m_collidablesToRecievers[collidable] = receiver;
		m_recieversToCollidables[receiver] = collidable;
		receiver->OnDispose = [&](const shared_ptr<ACollisionEventReceiver>& receiver) { return DisposeEventReceiver(receiver); };

	}
}

void CollisionManager::CheckOctrees(const shared_ptr<ACollisionAcceptor>& collidable)
{
	for (auto& volumeNameToOctree : m_volumeNameToOctree)
	{
		const OctreeChecker& octree = volumeNameToOctree.second;
		CheckOctreeHelper(octree, collidable);
	}
}

void CollisionManager::CheckOctree(const string& volumeName, const shared_ptr<ACollisionAcceptor>& collidable)
{
	if (m_volumeNameToOctree.find(volumeName) != m_volumeNameToOctree.end())
	{
		const OctreeChecker& octree = m_volumeNameToOctree[volumeName];
		CheckOctreeHelper(octree, collidable);
	}
}

void CollisionManager::DisposeEventReceiver(const shared_ptr<ACollisionEventReceiver>& receiver)
{
	if (m_recieversToCollidables.find(receiver) != m_recieversToCollidables.end())
	{
		const shared_ptr<ACollisionAcceptor>& disposedCollidable = m_recieversToCollidables[receiver];

		for (auto& collisionChannelNameToCollidables : m_channelNamesToCollidables)
		{
			vector<shared_ptr<ACollisionAcceptor>>& collidables = collisionChannelNameToCollidables.second;
			RemoveHelper(collidables, disposedCollidable);
		}

		for (auto& collisionRelationNameToCollidablePairs : m_relationNamesToGroups)
		{
			vector<shared_ptr<ACollisionAcceptor>>& collidableCheckers = collisionRelationNameToCollidablePairs.second.first;
			vector<shared_ptr<ACollisionAcceptor>>& collidableTargets = collisionRelationNameToCollidablePairs.second.second;
			RemoveHelper(collidableCheckers, disposedCollidable);
			RemoveHelper(collidableTargets, disposedCollidable);
		}

		for (auto& volumeNameToOctree : m_volumeNameToOctree)
		{
			OctreeChecker& octreeChecker = volumeNameToOctree.second;
			octreeChecker.RemoveCollidable(disposedCollidable);
		}

		m_collidablesToRecievers.erase(disposedCollidable);
		m_recieversToCollidables.erase(receiver);
	}
}

void CollisionManager::CheckChannelCollisionHelper(const vector<shared_ptr<ACollisionAcceptor>>& collidables)
{

	for (size_t reference_idx = 0; reference_idx < collidables.size(); ++reference_idx)
	{
		const shared_ptr<ACollisionAcceptor>& collidable1 = collidables[reference_idx];
		const shared_ptr<ACollisionEventReceiver>& receiver1 = m_collidablesToRecievers[collidable1];

		IntersectVisitor intersectVisitor(collidable1);
		for (size_t target_idx = reference_idx + 1; target_idx < collidables.size(); ++target_idx)
		{
			const shared_ptr<ACollisionAcceptor>& collidable2 = collidables[target_idx];

			if (collidable2->Accept(intersectVisitor))
			{

				const shared_ptr<ACollisionEventReceiver>& reciever2 = m_collidablesToRecievers[collidable2];

				if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
				if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
			}
		}
	}
}

void CollisionManager::CheckRelationCollisionHelper(const pair<vector<shared_ptr<ACollisionAcceptor>>, vector<shared_ptr<ACollisionAcceptor>>>& groups)
{
	const vector<shared_ptr<ACollisionAcceptor>>& collisionCheckers = groups.first;
	const vector<shared_ptr<ACollisionAcceptor>>& collisionTargets = groups.second;

	for (const shared_ptr<ACollisionAcceptor>& collisionChecker : collisionCheckers)
	{
		const shared_ptr<ACollisionEventReceiver>& receiver1 = m_collidablesToRecievers[collisionChecker];

		IntersectVisitor intersectVisitor(collisionChecker);
		for (const shared_ptr<ACollisionAcceptor>& collisionTarget : collisionTargets)
		{
			if (collisionTarget->Accept(intersectVisitor))
			{
				const shared_ptr<ACollisionEventReceiver>& reciever2 = m_collidablesToRecievers[collisionTarget];

				if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
				if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
			}
		}
	}
}

void CollisionManager::CheckOctreeHelper(const OctreeChecker& octreeChecker, const shared_ptr<ACollisionAcceptor>& collidable)
{
	const shared_ptr<ACollisionEventReceiver>& receiver1 = m_collidablesToRecievers[collidable];
	
	IntersectVisitor intersectVisitor(collidable);

	vector<shared_ptr<ACollisionAcceptor>> collisionCandidates = octreeChecker.GetCollisionCandidates(collidable);
	for (const shared_ptr<ACollisionAcceptor> collisionCandidate : collisionCandidates)
	{
		if (collisionCandidate->Accept(intersectVisitor))
		{
			const shared_ptr<ACollisionEventReceiver>& reciever2 = m_collidablesToRecievers[collisionCandidate];

			if (receiver1 != nullptr) receiver1->OnCollide(reciever2);
			if (reciever2 != nullptr) reciever2->OnCollide(receiver1);
		}
	}
}

void CollisionManager::RemoveHelper(vector<shared_ptr<ACollisionAcceptor>>& container, const shared_ptr<ACollisionAcceptor>& target)
{
	container.erase(
		remove_if(
			container.begin(),
			container.end(),
			[&](const shared_ptr<ACollisionAcceptor>& acceptor) {return acceptor == target; }
		),
		container.end()
	);
}
