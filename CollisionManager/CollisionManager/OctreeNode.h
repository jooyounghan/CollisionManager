#pragma once
#include "DirectXMath/DirectXCollision.h"
#include "ACollisionAcceptor.h"
#include <vector>
#include <memory>


struct OctreeNode : public DirectX::BoundingBox
{
	OctreeNode(const DirectX::BoundingBox& boundingBox, const uint32_t depthIn);

	bool isDivided = false;
	OctreeNode* parentOctree = nullptr;

	uint32_t depth;
	std::vector<std::shared_ptr<ACollisionAcceptor>> collidables;
	std::unique_ptr<OctreeNode> octrees[8];

	void Divide();
	void Merge();
	size_t GetCollidablesCount();

private:
	static void MergeRecursive(OctreeNode* octree, std::vector<std::shared_ptr<ACollisionAcceptor>>& collidables);
};
