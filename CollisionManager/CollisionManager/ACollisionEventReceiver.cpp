#include "pch.h"
#include "ACollisionEventReceiver.h"

using namespace std;

ACollisionEventReceiver::~ACollisionEventReceiver()
{
	OnDispose(shared_from_this());
}
