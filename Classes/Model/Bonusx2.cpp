#include "Bonusx2.h"
#include "Utility/Tags.h"
#include "Utility/XHelper.h"

Bonusx2::Bonusx2(){}
Bonusx2::~Bonusx2(){}

Bonusx2* Bonusx2::create(string fileName)
{
	Bonusx2* bonus = new Bonusx2();
	bonus->init(fileName);
	bonus->autorelease();
	return bonus;
}

bool Bonusx2::init(string fileName)
{
	if (!Node::init())
		return false;

	//---Khởi tạo sprite chính---
	_sprite = Sprite::create(fileName);
	_sprite->setPosition(0, 0);
	this->addChild(_sprite);


	//-------------   Physic Body  --------------
	body = PhysicsBody::createBox(_sprite->getBoundingBox().size, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
	body->setGravityEnable(false);
	body->setDynamic(false);
	body->setTag(Tags::BONUSX2);
	body->setCollisionBitmask(0x02);
	body->setContactTestBitmask(1);
	body->setCategoryBitmask(0x01);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);

	return true;
}

