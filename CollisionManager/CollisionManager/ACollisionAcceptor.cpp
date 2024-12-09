#include "pch.h"
#include "ACollisionAcceptor.h"

using namespace std;

void ACollisionAcceptor::SetUpdateHandler(const function<void(const ACollisionAcceptor*)>& onUpdate)
{
	OnUpdate = onUpdate;
}

void ACollisionAcceptor::Update()
{
	OnUpdate(this);
}
