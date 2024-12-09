#include "CollisionManager.h"
#include "ACollisionEventReceiver.h"
#include "CollidableSphere.h"
#include "CollidableOrientedBox.h"

#include <memory>
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
	virtual void OnCollide(ACollisionEventReceiver*) override;
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
	virtual void OnCollide(ACollisionEventReceiver*) override;
};

int main()
{
	int second = 0;
	CollisionManager test;

	Bat bat = Bat();
	std::vector<BaseBall> baseBalls;

	bat.box->Center = DirectX::XMFLOAT3(5.f, 0.f, 0.f);
	bat.box->Extents = DirectX::XMFLOAT3(1.f, 1.f, 1.f);

	DirectX::BoundingBox Box = DirectX::BoundingBox(DirectX::XMFLOAT3(0.f, 0.f, 0.f), DirectX::XMFLOAT3(100.f, 100.f, 100.f));


	while (true)
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		second++;
	}
}


void BaseBall::OnCollide(ACollisionEventReceiver* arg)
{
	Bat* bat = dynamic_cast<Bat*>(arg);
	if (bat != nullptr)
	{
		std::cout << "BaseBall :: Home Run!!" << std::endl;
	}
}

void Bat::OnCollide(ACollisionEventReceiver* arg)
{
	
	BaseBall* baseBall = dynamic_cast<BaseBall*>(arg);
	if (baseBall != nullptr)
	{
		std::cout << "Bat :: PIEW!!" << std::endl;
	}
}
