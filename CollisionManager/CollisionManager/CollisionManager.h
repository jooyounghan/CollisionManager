#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "ACollisionAcceptor.h"
#include "ACollisionEventReceiver.h"
#include "OctreeChecker.h"

class CollisionManager
{
private:
	std::unordered_map<std::string, std::vector<std::shared_ptr<ACollisionAcceptor>>> m_channelNamesToCollidables;

public:
	void CheckAllChannelCollision();
	void CheckChannelCollision(const std::string& channelName);

public:
	void RegisterCollidableForChannel(
		const std::string& channelName,
		const std::shared_ptr<ACollisionAcceptor>& collidable,
		const std::shared_ptr<ACollisionEventReceiver>& receiver
	);

private:
	std::unordered_map<std::string, std::pair<std::vector<std::shared_ptr<ACollisionAcceptor>>, std::vector<std::shared_ptr<ACollisionAcceptor>>>> m_relationNamesToGroups;

public:
	void CheckAllRelationCollision();
	void ChecRelationCollision(const std::string& relationName);

public:
	void RegisterCheckerCollidableForRelation(
		const std::string& channelName,
		const std::shared_ptr<ACollisionAcceptor>& collisionChecker,
		const std::shared_ptr<ACollisionEventReceiver>& checkerReceiver
	);

public:
	void RegisterTargetCollidableForRelation(
		const std::string& channelName,
		const std::shared_ptr<ACollisionAcceptor>& collisionTarget,
		const std::shared_ptr<ACollisionEventReceiver>& targetReceiver
	);

private:
	std::unordered_map<std::string, OctreeChecker> m_volumeNameToOctree;

public:
	void RegisterOctreeChecker(
		const std::string& volumeName, 
		const DirectX::BoundingBox& collisionVolume, 
		const size_t& maxCollidablesCountPerNode
	);

public:
	void RegisterCollidableToOctree(
		const std::string& volumeName,
		const std::shared_ptr<ACollisionAcceptor>& collidable,
		const std::shared_ptr<ACollisionEventReceiver>& receiver
	);

public:
	void CheckOctrees(const std::shared_ptr<ACollisionAcceptor>& collidable);
	void CheckOctree(const std::string& volumeName, const std::shared_ptr<ACollisionAcceptor>& collidable);

private:
	std::unordered_map<std::shared_ptr<ACollisionAcceptor>, std::shared_ptr<ACollisionEventReceiver>> m_collidablesToRecievers;
	std::unordered_map<std::shared_ptr<ACollisionEventReceiver>, std::shared_ptr<ACollisionAcceptor>> m_recieversToCollidables;


public:
	void DisposeEventReceiver(const std::shared_ptr<ACollisionEventReceiver>& receiver);

private:
	void CheckChannelCollisionHelper(const std::vector<std::shared_ptr<ACollisionAcceptor>>& collidables);
	void CheckRelationCollisionHelper(const std::pair< std::vector<std::shared_ptr<ACollisionAcceptor>>, std::vector<std::shared_ptr<ACollisionAcceptor>>>& groups);
	void CheckOctreeHelper(const OctreeChecker& octreeChecker, const std::shared_ptr<ACollisionAcceptor>& collidable);

private:
	void RemoveHelper(std::vector<std::shared_ptr<ACollisionAcceptor>>& container, const std::shared_ptr<ACollisionAcceptor>& target);
};