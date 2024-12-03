#pragma once
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <functional>

class ACollisionEventReceiver : public std::enable_shared_from_this<ACollisionEventReceiver>
{
public:
    ACollisionEventReceiver() = default;

public:
    virtual ~ACollisionEventReceiver();

    std::function<void(const std::shared_ptr<ACollisionEventReceiver>&)> OnDispose
        = [](const std::shared_ptr<ACollisionEventReceiver>&) {};
    virtual void OnCollide(const std::shared_ptr<ACollisionEventReceiver>&) = 0;

public:
    template <typename Derived, typename... Args>
    static std::shared_ptr<Derived> Create(Args&&... args)
    {
        static_assert(std::is_base_of<ACollisionEventReceiver, Derived>::value,
            "Derived must inherit from ACollisionEventReceiver.");

        std::shared_ptr<Derived> ptr = std::make_shared<Derived>(std::forward<Args>(args)...);
        return ptr;
    }
};