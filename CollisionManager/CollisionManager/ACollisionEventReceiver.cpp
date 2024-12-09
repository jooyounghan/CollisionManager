#include "pch.h"
#include "ACollisionEventReceiver.h"

using namespace std;

ACollisionEventReceiver::~ACollisionEventReceiver()
{
	OnDispose(this);
}

void ACollisionEventReceiver::SetDisposeHandler(const function<void(ACollisionEventReceiver*)>& onDispose)
{
	OnDispose = onDispose;
}
