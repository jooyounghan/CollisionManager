#include "pch.h"
#include "OctreeNode.h"

using namespace std;
using namespace DirectX;

OctreeNode::OctreeNode(const BoundingBox& boundingBox, const uint32_t depthIn)
	: BoundingBox(boundingBox), depth(depthIn)
{

}

void OctreeNode::Divide()
{
	if (!isDivided)
	{
		isDivided = true;

		const float halfXExtent = Extents.x / 2.f;
		const float halfYExtent = Extents.y / 2.f;
		const float halfZExtent = Extents.z / 2.f;

		for (size_t x_idx = 0; x_idx < 2; x_idx++)
		{
			float xCenter = Center.x + halfXExtent * (x_idx % 2 == 0 ? 1.f : -1.f);
			for (size_t y_idx = 0; y_idx < 2; y_idx++)
			{
				float yCenter = Center.y + halfYExtent * (y_idx % 2 == 0 ? 1.f : -1.f);
				for (size_t z_idx = 0; z_idx < 2; z_idx++)
				{
					float zCenter = Center.z + halfZExtent * (z_idx % 2 == 0 ? 1.f : -1.f);
					octrees[z_idx + 2 * y_idx + 4 * x_idx] = make_unique<OctreeNode>(
						BoundingBox(XMFLOAT3(xCenter, yCenter, zCenter), XMFLOAT3(halfXExtent, halfYExtent, halfZExtent)), depth + 1
					);
					octrees[z_idx + 2 * y_idx + 4 * x_idx]->parentOctree = this;
				}
			}
		}

		for (const shared_ptr<ACollisionAcceptor>& collidable : collidables)
		{
			for (size_t octree_idx = 0; octree_idx < 8; ++octree_idx)
			{
				OctreeNode* octree = octrees[octree_idx].get();
				const BoundingBox& octreeVolume = *octree;
				if (collidable->IsInVolume(octreeVolume))
				{
					octree->collidables.push_back(collidable);
					break;
				}
				else if (collidable->IsIntersectWithVolume(octreeVolume))
				{
					octree->collidables.push_back(collidable);
					continue;
				}
				else;
			}
		}
		collidables.clear();
	}
}

void OctreeNode::Merge()
{
	MergeRecursive(this, collidables);
}

size_t OctreeNode::GetCollidablesCount()
{
	size_t result = 0;
	if (isDivided)
	{
		for (const unique_ptr<OctreeNode>& octree : octrees)
		{
			result += octree->GetCollidablesCount();
		}
	}
	else
	{
		result = collidables.size();
	}
	return result;
}

void OctreeNode::MergeRecursive(
	OctreeNode* octree, 
	vector<shared_ptr<ACollisionAcceptor>>& collidables
)
{
	if (octree->isDivided)
	{
		octree->isDivided = false;
		for (unique_ptr<OctreeNode>& octree : octree->octrees)
		{
			if (octree != nullptr)
			{
				MergeRecursive(octree.get(), collidables);
				octree.reset();
				octree = nullptr;
			}
		}
	}
	else
	{
		for (const shared_ptr<ACollisionAcceptor>& collidable : octree->collidables)
		{
			collidables.emplace_back(collidable);
		}
	}
}

