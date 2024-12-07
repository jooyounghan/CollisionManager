#include "pch.h"
#include "OctreeChecker.h"

using namespace std;

OctreeChecker::OctreeChecker() : m_maxCollidablesCountPerNode(0) {}

OctreeChecker::OctreeChecker(const DirectX::BoundingBox& collisionVolume, const size_t& maxCollidablesCountPerNode)
	: m_rootNode(make_unique<OctreeNode>(collisionVolume, 0)), m_maxCollidablesCountPerNode(maxCollidablesCountPerNode)
{

}

void OctreeChecker::InsertCollidable(const shared_ptr<ACollisionAcceptor>& collidable)
{
	InsertRecursive(m_rootNode, collidable);
}

void OctreeChecker::RemoveCollidable(const shared_ptr<ACollisionAcceptor>& collidable)
{
	ACollisionAcceptor* _collidable = collidable.get();
	vector<OctreeNode*>& octrees = m_collidablesToNodes[_collidable];

	for (OctreeNode* octree : octrees)
	{
		vector<shared_ptr<ACollisionAcceptor>>& collidables = octree->collidables;
		collidables.erase(
			remove_if(collidables.begin(), collidables.end(),
				[&](const shared_ptr<ACollisionAcceptor>& _collidable) {
					return _collidable == collidable;
				}),
			collidables.end()
		);
	}
	octrees.clear();
	RestructOctree();
}

void OctreeChecker::UpdateCollidable(const shared_ptr<ACollisionAcceptor>& collidable)
{
	RemoveCollidable(collidable);
	InsertCollidable(collidable);
}

vector<shared_ptr<ACollisionAcceptor>> OctreeChecker::GetCollisionCandidates(const shared_ptr<ACollisionAcceptor>& collidable) const
{
	vector<shared_ptr<ACollisionAcceptor>> result;
	ACollisionAcceptor* _collidable = collidable.get();
	if (m_collidablesToNodes.find(_collidable) != m_collidablesToNodes.end())
	{
		const std::vector<OctreeNode*>& octreeNodes = m_collidablesToNodes.at(_collidable);

		for (OctreeNode* octreeNode : octreeNodes)
		{
			const vector<shared_ptr<ACollisionAcceptor>>& collidables = octreeNode->collidables;
			result.insert(result.end(), collidables.begin(), collidables.end());
		}
	}
	return result;
}

void OctreeChecker::InsertRecursive(const unique_ptr<OctreeNode>& node, const shared_ptr<ACollisionAcceptor>& collidable)
{
	if (!node->isDivided)
	{
		if (node->collidables.size() < m_maxCollidablesCountPerNode)
		{
			const OctreeNode& octree = *node;
			if (!collidable->IsDisjointWithVolume(octree))
			{
				node->collidables.push_back(collidable);
				m_collidablesToNodes[collidable.get()].emplace_back(node.get());

				collidable->OnUpdate = [&](const shared_ptr<ACollisionAcceptor>& collidable) {UpdateCollidable(collidable); };
			}
			return;
		}
		else
		{
			node->Divide();
		}
	}

	for (const unique_ptr<OctreeNode>& octree : node->octrees)
	{
		InsertRecursive(octree, collidable);
	}
}

void OctreeChecker::RestructOctree()
{
	RestructOctreeRecursive(m_rootNode);
}

void OctreeChecker::RestructOctreeRecursive(const unique_ptr<OctreeNode>& node)
{
	if (node->GetCollidablesCount() <= m_maxCollidablesCountPerNode)
	{
		node->Merge();
		return;
	}
	for (const unique_ptr<OctreeNode>& octree : node->octrees)
	{
		RestructOctreeRecursive(octree);
	}
}
