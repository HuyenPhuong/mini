#include "Coin.h"
#include "Utility/Tags.h"
#include "Utility/XHelper.h"

Coin::Coin(){}
Coin::~Coin(){}

Coin* Coin::create(string fileName)
{
	Coin* coin = new Coin();
	coin->init(fileName);
	coin->autorelease();
	return coin;
}

bool Coin::init(string fileName)
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
	body->setTag(Tags::COIN);
	body->setCollisionBitmask(0x02);
	body->setContactTestBitmask(1);
	body->setCategoryBitmask(0x01);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);
	
	return true;
}

//Animation
void Coin::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation(name, count, time, true, this->_sprite);
}
