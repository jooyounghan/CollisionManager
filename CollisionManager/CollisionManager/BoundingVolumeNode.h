#pragma once
#include <DirectXCollision.h>
#include "ACollisionAcceptor.h"
#include <vector>

class BoundingVolumeNode : public DirectX::BoundingBox
{
public:
	BoundingVolumeNode(
		const DirectX::BoundingBox boundingBox, 
		ACollisionAcceptor* const collidable = nullptr
	);
	BoundingVolumeNode(
		const DirectX::XMFLOAT3& lowerBound, 
		const DirectX::XMFLOAT3& upperBound, 
		ACollisionAcceptor* const collidable = nullptr
	);

private:
	DirectX::XMFLOAT3 m_lowerBound;
	DirectX::XMFLOAT3 m_upperBound;

public:
	BoundingVolumeNode* m_parentNode = nullptr;
	float m_volumeSize = 0.f;

public:
	BoundingVolumeNode* m_left;
	BoundingVolumeNode* m_right;

public:
	ACollisionAcceptor* m_collidable;

public:
	inline const float GetVolumeSize() const { return (Extents.x * 2) * (Extents.y * 2) * (Extents.z * 2); }
	inline const bool IsLeaf() const { return m_collidable != nullptr; }

public:
	static BoundingVolumeNode* CreateUnionBoundingVolume(
		const BoundingVolumeNode* const boundingVolume1,
		const BoundingVolumeNode* const boundingVolume2,
		const float& margin
	);

	static const float GetUnionBoundingVolumeSize(
		const BoundingVolumeNode* boundingVolume1,
		const BoundingVolumeNode* boundingVolume2,
		const float& margin
	);

	static void FindBestLeafNode(
		BoundingVolumeNode* const targetNode,
		const BoundingVolumeNode* const insertNode,
		const float& margin,
		float& minVolumeSize,
		BoundingVolumeNode*& bestSiblingLeafNode
	);

private:
	static void GetBounds(
		const BoundingVolumeNode* const boundingVolume1,
		const BoundingVolumeNode* const boundingVolume2,
		const float& margin,
		DirectX::XMFLOAT3& lowerBoundOut,
		DirectX::XMFLOAT3& upperBoundOut
	);

};

