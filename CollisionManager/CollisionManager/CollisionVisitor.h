#pragma once
#include <memory>
#include "CollidableSphere.h"
#include "CollidableOrientedBox.h"
#include "CollidableFrustum.h"

class ICollisionVisitor
{
public:
	virtual bool Visit(CollidableSphere* collidableSphere) const = 0;
	virtual bool Visit(CollidableOrientedBox* collidableSphere) const = 0;
	virtual bool Visit(CollidableFrustum* collidableSphere) const = 0;
};

class ACollisionVisitor : public ICollisionVisitor
{
public:
	ACollisionVisitor(const std::shared_ptr<ICollisionAcceptor>& collisionAcceptor);

protected:
	std::shared_ptr<ICollisionAcceptor> m_collisionAcceptor;
};

template<typename T>
class ACollisionSpecifiedVisitor : public ICollisionVisitor
{
public:
	ACollisionSpecifiedVisitor(T* specifiedCollisionAcceptor);

public:
	T* m_specifiedCollisionAccpetor;
};

template<typename T>
ACollisionSpecifiedVisitor<T>::ACollisionSpecifiedVisitor(T* specifiedCollisionAcceptor)
	: m_specifiedCollisionAccpetor(specifiedCollisionAcceptor)
{
}
