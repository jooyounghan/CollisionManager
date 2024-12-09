#include "pch.h"
#include "BoundingVolumeHierachy.h"

using namespace std;
using namespace DirectX;

BoundingVolumeHierachy::BoundingVolumeHierachy(const float& margin)
	: m_margin(margin)
{
}

void BoundingVolumeHierachy::InsertCollidable(ACollisionAcceptor* collidable)
{
	BoundingVolumeNode* leafNode = new BoundingVolumeNode(collidable->GetBoundingBox(m_margin), collidable);
	m_collidablesToNode.emplace(collidable, leafNode);

	float minVolumeSize = FLT_MAX;
	BoundingVolumeNode* bestLeafNode = nullptr;

	BoundingVolumeNode::FindBestLeafNode(m_rootNode, leafNode, m_margin, minVolumeSize, bestLeafNode);

	if (bestLeafNode != nullptr)
	{
		BoundingVolumeNode* newInternalNode = BoundingVolumeNode::CreateUnionBoundingVolume(leafNode, bestLeafNode, m_margin);

		BoundingVolumeNode* parent = bestLeafNode->m_parentNode;

		if (parent->m_left == bestLeafNode)
		{
			parent->m_left = newInternalNode;
		}
		else
		{
			parent->m_right = newInternalNode;
		}
		newInternalNode->m_parentNode = parent;

		leafNode->m_parentNode = newInternalNode;
		bestLeafNode->m_parentNode = newInternalNode;

		newInternalNode->m_left = leafNode;
		newInternalNode->m_right = bestLeafNode;

		RestructVolume(newInternalNode);
	}
	else
	{
		m_rootNode = leafNode;
	}
}

void BoundingVolumeHierachy::RemoveCollidable(ACollisionAcceptor* collidable)
{
	if (m_collidablesToNode.find(collidable) != m_collidablesToNode.end())
	{
		BoundingVolumeNode* boundingVolumeNode = m_collidablesToNode[collidable];
		m_collidablesToNode.erase(collidable);

		BoundingVolumeNode* parentNode = boundingVolumeNode->m_parentNode;
		if (parentNode == nullptr)
		{
			delete boundingVolumeNode;
			m_rootNode = nullptr;
			return;
		}

		BoundingVolumeNode* grandParentNode = parentNode->m_parentNode;
		if (grandParentNode == nullptr)
		{
			if (parentNode->m_left == boundingVolumeNode)
			{
				m_rootNode = parentNode->m_right;

			}
			else
			{
				m_rootNode = parentNode->m_left;
			}
			m_rootNode->m_parentNode = nullptr;
			delete boundingVolumeNode;
			delete parentNode;
			return;
		}

		BoundingVolumeNode* siblingNode = nullptr;
		if (parentNode->m_left == boundingVolumeNode)
		{
			siblingNode = parentNode->m_right;

		}
		else
		{
			siblingNode = parentNode->m_left;
		}

		if (grandParentNode->m_left == parentNode)
		{
			grandParentNode->m_right = siblingNode;
		}
		else
		{
			grandParentNode->m_left = siblingNode;
		}
		siblingNode->m_parentNode = grandParentNode;
		delete boundingVolumeNode;
		delete parentNode;

		/*
		지웠을 때는 볼륨에 대해서 재구성하지 않고, 다른 원소가 삽입되거나 할 경우에만!		
		*/ 
	}
}

void BoundingVolumeHierachy::RestructVolume(BoundingVolumeNode* node)
{
	BoundingVolumeNode* parentNode = node->m_parentNode;
	if (parentNode == nullptr)
	{
		return;
	}

	if (parentNode->m_volumeSize != BoundingVolumeNode::GetUnionBoundingVolumeSize(parentNode->m_left, parentNode->m_right, m_margin))
	{
		BoundingVolumeNode* restructedNode = BoundingVolumeNode::CreateUnionBoundingVolume(parentNode->m_left, parentNode->m_right, m_margin);

		bool isNodeLeft = false;
		if (parentNode->m_left == node)
		{
			isNodeLeft = true;
		}

		restructedNode->m_left = parentNode->m_left;
		restructedNode->m_right = parentNode->m_right;
		parentNode->m_left->m_parentNode = restructedNode;
		parentNode->m_right->m_parentNode = restructedNode;

		BoundingVolumeNode* grandParentNode = parentNode->m_parentNode;
		if (grandParentNode == nullptr)
		{
			delete parentNode;
			m_rootNode = restructedNode;
			return;
		}

		BoundingVolumeNode* sibling = nullptr;
		bool isSiblingLeft = false;
		if (grandParentNode->m_left == restructedNode)
		{
			grandParentNode->m_left = restructedNode;
			sibling = grandParentNode->m_right;
		}
		else
		{
			grandParentNode->m_right = restructedNode;
			sibling = grandParentNode->m_left;
			isSiblingLeft = true;
		}
		restructedNode->m_parentNode = grandParentNode;
		delete parentNode;

		// Rotate
		if (sibling->IsLeaf())
		{
			if (isSiblingLeft)
			{
				grandParentNode->m_right = node;
			}
			else
			{
				grandParentNode->m_left = node;
			}
			node->m_parentNode = grandParentNode;

			if (isNodeLeft)
			{
				restructedNode->m_left = sibling;
			}
			else
			{
				restructedNode->m_right = sibling;
			}
			sibling->m_parentNode = restructedNode;
		}
		
		RestructVolume(parentNode);
	}


	if (node != nullptr && node->m_left != nullptr && node->m_right != nullptr)
	{
		// 기존 볼륨 사이즈와 달라졌을 경우,
		if (node->m_volumeSize != BoundingVolumeNode::GetUnionBoundingVolumeSize(node->m_left, node->m_right, m_margin))
		{

		}
	}
}
