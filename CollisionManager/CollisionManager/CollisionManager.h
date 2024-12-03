#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "ICollisionAcceptor.h"
#include "ACollisionEventReceiver.h"

class CollisionManager
{
public:
	std::unordered_map<std::string, std::vector<std::shared_ptr<ICollisionAcceptor>>> m_channelNamesToCollidables;

public:
	std::unordered_map<std::string, std::pair<std::vector<std::shared_ptr<ICollisionAcceptor>>, std::vector<std::shared_ptr<ICollisionAcceptor>>>> m_relationNamesToGroups;

public:
	std::unordered_map<std::shared_ptr<ICollisionAcceptor>, std::shared_ptr<ACollisionEventReceiver>> m_collidablesToRecievers;
	std::unordered_map<std::shared_ptr<ACollisionEventReceiver>, std::shared_ptr<ICollisionAcceptor>> m_recieversToCollidables;

public:
	void CheckAllChannelCollision();
	void CheckChannelCollision(const std::string& channelName);

public:
	void RegisterCollidableForChannel(
		const std::string& channelName,
		const std::shared_ptr<ICollisionAcceptor>& collidable,
		const std::shared_ptr<ACollisionEventReceiver>& receiver
	);

public:
	void CheckAllRelationCollision();
	void ChecRelationCollision(const std::string& relationName);

public:
	void RegisterCheckerCollidableForRelation(
		const std::string& channelName,
		const std::shared_ptr<ICollisionAcceptor>& collisionChecker,
		const std::shared_ptr<ACollisionEventReceiver>& checkerReceiver
	);

public:
	void RegisterTargetCollidableForRelation(
		const std::string& channelName,
		const std::shared_ptr<ICollisionAcceptor>& collisionTarget,
		const std::shared_ptr<ACollisionEventReceiver>& targetReceiver
	);

public:
	void DisposeEventReceiver(const std::shared_ptr<ACollisionEventReceiver>& receiver);


private:
	void CheckChannelCollisionHelper(const std::vector<std::shared_ptr<ICollisionAcceptor>>& collidables);
	void CheckRelationCollisionHelper(const std::pair< std::vector<std::shared_ptr<ICollisionAcceptor>>, std::vector<std::shared_ptr<ICollisionAcceptor>>>& groups);
};