#pragma once
#include "BoundingVolumeNode.h"

#include <unordered_map>

class BoundingVolumeHierachy
{
public:
	BoundingVolumeHierachy(const float& margin);

private:
	BoundingVolumeNode* m_rootNode = nullptr;

private:
	std::unordered_map<ACollisionAcceptor*, BoundingVolumeNode*> m_collidablesToNode;

private:
	const float m_margin;


public:
	void InsertCollidable(ACollisionAcceptor* collidable);
	void RemoveCollidable(ACollisionAcceptor* collidable);

private:
	void RestructVolume(BoundingVolumeNode* node);

};

