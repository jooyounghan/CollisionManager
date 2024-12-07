#pragma once
#include "OctreeNode.h"
#include <unordered_map>

class OctreeChecker
{
public:
	OctreeChecker();
	OctreeChecker(const DirectX::BoundingBox& collisionVolume, const size_t& maxCollidablesCountPerNode);

private:
	const size_t m_maxCollidablesCountPerNode;
	std::unique_ptr<OctreeNode> m_rootNode;
	std::unordered_map<ACollisionAcceptor*, std::vector<OctreeNode*>> m_collidablesToNodes;

public:
	void InsertCollidable(const std::shared_ptr<ACollisionAcceptor>& collidable);
	void RemoveCollidable(const std::shared_ptr<ACollisionAcceptor>& collidable);
	void UpdateCollidable(const std::shared_ptr<ACollisionAcceptor>& collidable);
	std::vector<std::shared_ptr<ACollisionAcceptor>> GetCollisionCandidates(const std::shared_ptr<ACollisionAcceptor>& collidable) const;


private:
	void InsertRecursive(const std::unique_ptr<OctreeNode>& node, const std::shared_ptr<ACollisionAcceptor>& collidable);

private:
	void RestructOctree();
	void RestructOctreeRecursive(const std::unique_ptr<OctreeNode>& node);

};

