#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "ICollisionAcceptor.h"
#include "ICollisionEventReceiver.h"

class CollisionManager
{
public:
	std::unordered_map<std::string, std::vector<std::shared_ptr<ICollisionAcceptor>>> m_collisionChannelNamesToCollidables;

public:
	std::unordered_map<std::shared_ptr<ICollisionAcceptor>, std::shared_ptr<ICollisionEventReceiver>> m_collidablesToRecievers;

public:
	void CheckAllCollision();
	void CheckCollision(const std::string& channelName);

private:
	void CheckCollisionHelper(const std::vector<std::shared_ptr<ICollisionAcceptor>>& collidables);
};