#include "pch.h"
#include "BoundingVolumeNode.h"

using namespace std;
using namespace DirectX;

BoundingVolumeNode::BoundingVolumeNode(
	const BoundingBox boundingBox, 
	ACollisionAcceptor* const collidable
)
	: BoundingBox(boundingBox),
	m_lowerBound(
		boundingBox.Center.x - Extents.x,
		boundingBox.Center.y - Extents.y,
		boundingBox.Center.z - Extents.z
	),
	m_upperBound(
		boundingBox.Center.x + Extents.x,
		boundingBox.Center.y + Extents.y,
		boundingBox.Center.z + Extents.z
	),
	m_collidable(collidable)
{
	m_volumeSize = GetVolumeSize();
}

BoundingVolumeNode::BoundingVolumeNode(
	const XMFLOAT3& lowerBound,
	const XMFLOAT3& upperBound,
	ACollisionAcceptor* const collidable
)
	: BoundingBox(
		XMFLOAT3(
			(lowerBound.x + upperBound.x) / 2.f,
			(lowerBound.y + upperBound.y) / 2.f,
			(lowerBound.z + upperBound.z) / 2.f
		), 
		XMFLOAT3(
			(upperBound.x - lowerBound.x / 2.f),
			(upperBound.y - lowerBound.y / 2.f),
			(upperBound.z - lowerBound.z / 2.f)
		)
	),
	m_lowerBound(lowerBound), m_upperBound(upperBound), m_collidable(collidable)
{
	m_volumeSize = GetVolumeSize();
}

BoundingVolumeNode* BoundingVolumeNode::CreateUnionBoundingVolume(
	const BoundingVolumeNode* const boundingVolume1,
	const BoundingVolumeNode* const boundingVolume2,
	const float& margin
)
{
	XMFLOAT3 lowerBound;
	XMFLOAT3 upperBound;
	GetBounds(boundingVolume1, boundingVolume2, margin, lowerBound, upperBound);

	return new BoundingVolumeNode(lowerBound, upperBound);
}

const float BoundingVolumeNode::GetUnionBoundingVolumeSize(
	const BoundingVolumeNode* const boundingVolume1,
	const BoundingVolumeNode* const boundingVolume2,
	const float& margin
)
{
	XMFLOAT3 lowerBound;
	XMFLOAT3 upperBound;
	GetBounds(boundingVolume1, boundingVolume2, margin, lowerBound, upperBound);

	return (upperBound.x - lowerBound.x) * (upperBound.y - lowerBound.y) * (upperBound.z - lowerBound.z);
}

void BoundingVolumeNode::GetBounds(
	const BoundingVolumeNode* const boundingVolume1,
	const BoundingVolumeNode* const boundingVolume2,
	const float& margin,
	XMFLOAT3& lowerBoundOut, 
	XMFLOAT3& upperBoundOut
)
{
	lowerBoundOut.x = std::min(boundingVolume1->m_lowerBound.x, boundingVolume2->m_lowerBound.x);
	lowerBoundOut.y = std::min(boundingVolume1->m_lowerBound.y, boundingVolume2->m_lowerBound.y);
	lowerBoundOut.z = std::min(boundingVolume1->m_lowerBound.z, boundingVolume2->m_lowerBound.z);

	upperBoundOut.x = std::max(boundingVolume1->m_upperBound.x, boundingVolume2->m_upperBound.x);
	upperBoundOut.y = std::max(boundingVolume1->m_upperBound.y, boundingVolume2->m_upperBound.y);
	upperBoundOut.z = std::max(boundingVolume1->m_upperBound.z, boundingVolume2->m_upperBound.z);

	lowerBoundOut.x -= margin;
	lowerBoundOut.y -= margin;
	lowerBoundOut.z -= margin;

	upperBoundOut.x += margin;
	upperBoundOut.y += margin;
	upperBoundOut.z += margin;
}

void BoundingVolumeNode::FindBestLeafNode(
	BoundingVolumeNode* const targetNode,
	const BoundingVolumeNode* const insertNode,
	const float& margin,
	float& minVolumeSize,
	BoundingVolumeNode*& bestSiblingLeafNode
)
{
	if (targetNode != nullptr)
	{
		const float volumeSize = GetUnionBoundingVolumeSize(targetNode, insertNode, margin);
		if (minVolumeSize > volumeSize)
		{
			minVolumeSize = volumeSize;
			if (targetNode->IsLeaf())
			{
				bestSiblingLeafNode = targetNode;
			}
			else
			{
				FindBestLeafNode(targetNode->m_left, insertNode, margin, minVolumeSize, bestSiblingLeafNode);
				FindBestLeafNode(targetNode->m_right, insertNode, margin, minVolumeSize, bestSiblingLeafNode);
			}
		}
	}

}
