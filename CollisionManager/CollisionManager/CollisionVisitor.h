#pragma once
#include "CollidableSphere.h"
#include "CollidableOrientedBox.h"
#include "CollidableFrustum.h"

class ICollisionVisitor
{
public:
	virtual bool Visit(const CollidableSphere* const collidableSphere) const = 0;
	virtual bool Visit(const CollidableOrientedBox* const collidableSphere) const = 0;
	virtual bool Visit(const CollidableFrustum* const collidableSphere) const = 0;
};

class ACollisionVisitor : public ICollisionVisitor
{
public:
	ACollisionVisitor(ACollisionAcceptor* collisionAcceptor);

protected:
	ACollisionAcceptor* m_collisionAcceptor;
};

template<typename T>
class ACollisionSpecifiedVisitor : public ICollisionVisitor
{
public:
	ACollisionSpecifiedVisitor(const T* const specifiedCollisionAcceptor);

public:
	const T* const  m_specifiedCollisionAccpetor;
};

template<typename T>
ACollisionSpecifiedVisitor<T>::ACollisionSpecifiedVisitor(const T* const specifiedCollisionAcceptor)
	: m_specifiedCollisionAccpetor(specifiedCollisionAcceptor)
{
}
