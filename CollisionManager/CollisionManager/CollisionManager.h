#pragma once
#include <string>
#include <unordered_map>

#include "ACollisionAcceptor.h"
#include "ACollisionEventReceiver.h"

class CollisionManager
{
private:
	std::unordered_map<std::string, std::vector<ACollisionAcceptor*>> m_channelNamesToCollidables;

public:
	void CheckAllChannelCollision();
	void CheckChannelCollision(const std::string& channelName);

public:
	void RegisterCollidableForChannel(
		const std::string& channelName,
		ACollisionAcceptor* const collidable,
		ACollisionEventReceiver* const receiver
	);

private:
	std::unordered_map<std::string, std::pair<std::vector<ACollisionAcceptor*>, std::vector<ACollisionAcceptor*>>> m_relationNamesToGroups;

public:
	void CheckAllRelationCollision();
	void ChecRelationCollision(const std::string& relationName);

public:
	void RegisterCheckerCollidableForRelation(
		const std::string& channelName,
		ACollisionAcceptor* const collisionChecker,
		ACollisionEventReceiver* const checkerReceiver
	);

public:
	void RegisterTargetCollidableForRelation(
		const std::string& channelName,
		ACollisionAcceptor* const collisionTarget,
		ACollisionEventReceiver* const targetReceiver
	);

private:
	std::unordered_map<ACollisionAcceptor*, ACollisionEventReceiver*> m_collidablesToRecievers;
	std::unordered_map<ACollisionEventReceiver*, ACollisionAcceptor*> m_recieversToCollidables;


public:
	void DisposeEventReceiver(ACollisionEventReceiver* const receiver );

private:
	void CheckChannelCollisionHelper(const std::vector<ACollisionAcceptor*>& collidables);
	void CheckRelationCollisionHelper(const std::pair<std::vector<ACollisionAcceptor*>, std::vector<ACollisionAcceptor*>>& groups);

private:
	void RemoveHelper(std::vector<ACollisionAcceptor*>& container, const ACollisionAcceptor* const target);
};