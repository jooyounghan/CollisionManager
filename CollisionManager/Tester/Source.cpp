#include "CollisionManager.h"
#include "ACollisionEventReceiver.h"
#include "CollidableSphere.h"
#include "CollidableOrientedBox.h"

#include <thread>
#include <iostream>
#include <format>
#include <string>


class BaseBall : public ACollisionEventReceiver
{
public:
	BaseBall() = default;

public:
	virtual ~BaseBall() {};

public:
	std::shared_ptr<CollidableSphere> sphere = std::make_shared<CollidableSphere>();

public:
	virtual void OnCollide(const std::shared_ptr<ACollisionEventReceiver>&) override;
};

class Bat : public ACollisionEventReceiver
{
public:
	Bat() = default;

public:
	virtual ~Bat() {};

public:
	std::shared_ptr<CollidableOrientedBox> box = std::make_shared<CollidableOrientedBox>();

public:
	virtual void OnCollide(const std::shared_ptr<ACollisionEventReceiver>&) override;
};

int main()
{
	int second = 0;
	CollisionManager test;


	std::shared_ptr<BaseBall> baseBall = ACollisionEventReceiver::Create<BaseBall>();	
	std::shared_ptr<Bat> bat = ACollisionEventReceiver::Create<Bat>();

	baseBall->sphere->Center = DirectX::XMFLOAT3(-5.f, 0.f, 0.f);
	baseBall->sphere->Radius = 1.f;

	bat->box->Center = DirectX::XMFLOAT3(5.f, 0.f, 0.f);
	bat->box->Extents = DirectX::XMFLOAT3(1.f, 1.f, 1.f);

	test.RegisterCollidableForChannel("BaseBall", baseBall->sphere, baseBall);
	test.RegisterCollidableForChannel("BaseBall", bat->box, bat);

	test.RegisterCheckerCollidableForRelation("BaseBall", baseBall->sphere, baseBall);
	test.RegisterTargetCollidableForRelation("BaseBall", bat->box, bat);

	while (true)
	{
		std::cout << std::format("{} second...", std::to_string(second / 10.f)) << std::endl;
		test.CheckAllChannelCollision();
		test.CheckAllRelationCollision();

		baseBall->sphere->Center.x += 2.5f;
		bat->box->Center.x -= 2.5f;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		second++;
	}
}


void BaseBall::OnCollide(const std::shared_ptr<ACollisionEventReceiver>& arg)
{
	std::shared_ptr<Bat> bat = dynamic_pointer_cast<Bat>(arg);
	if (bat != nullptr)
	{
		std::cout << "BaseBall :: Home Run!!" << std::endl;
	}
}

void Bat::OnCollide(const std::shared_ptr<ACollisionEventReceiver>& arg)
{
	std::shared_ptr<BaseBall> baseBall = dynamic_pointer_cast<BaseBall>(arg);
	if (baseBall != nullptr)
	{
		std::cout << "Bat :: PIEW!!" << std::endl;
	}
}
