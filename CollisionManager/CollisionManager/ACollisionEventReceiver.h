#pragma once
#include <stdexcept>
#include <type_traits>
#include <functional>

class ACollisionEventReceiver
{
public:
    ACollisionEventReceiver() = default;

public:
    virtual ~ACollisionEventReceiver();

protected:
    std::function<void(ACollisionEventReceiver*)> OnDispose
        = [](ACollisionEventReceiver*) {};

public:
    void SetDisposeHandler(const std::function<void(ACollisionEventReceiver*)>& onDispose);

public:
    virtual void OnCollide(ACollisionEventReceiver*) = 0;
};