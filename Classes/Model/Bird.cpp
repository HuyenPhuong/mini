/*
 * Bird.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: Dang
 */

#include "Bird.h"
#include "Utility/Tags.h"
#include "Utility/Config.h"
#include "Utility/XHelper.h"

Bird::Bird() {
	// TODO Auto-generated constructor stub

}

Bird::~Bird() {
	// TODO Auto-generated destructor stub
}

Bird* Bird::create(string fileName)
{
	Bird* bird = new Bird();
	bird->init(fileName);
	bird->autorelease();
	return bird;
}

bool Bird::init(string fileName)
{
	if (!Node::init())
			return false;

		//---Khởi tạo sprite chính---
		_sprite = Sprite::create(fileName);
		_sprite->setPosition(0, 0);
		this->addChild(_sprite);


		//-------------   Physic Body  --------------
		//body = PhysicsBody::createBox(_sprite->getBoundingBox().size, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
		body = PhysicsBody::createCircle(_sprite->getContentSize().width / 2, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
		body->setGravityEnable(false);
		body->setDynamic(false);
		body->setTag(Tags::BIRD);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(1);
		body->setCategoryBitmask(0x01);
		this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->setPhysicsBody(body);

		//Score
		auto nodeScore = Node::create();
		nodeScore->setPosition(Point::ZERO);
		nodeScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(nodeScore);
		PhysicsBody * bodyNodeScore = PhysicsBody::createBox(Size(_sprite->getContentSize().width * 2.5 / 5, Config::screenSize.height*4), PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
		bodyNodeScore->setTag(Tags::NODE_SCORE);
		bodyNodeScore->setDynamic(false);
		bodyNodeScore->setCategoryBitmask(0x01);
		bodyNodeScore->setContactTestBitmask(1);
		bodyNodeScore->setCollisionBitmask(0x02);
		nodeScore->setPhysicsBody(bodyNodeScore);

		return true;
}

void Bird::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation(name, count, time, true, this->_sprite);
}

void Bird::MoveBird(float speed)
{
	auto moveBird = MoveBy::create(100/speed, Vec2(- Config::screenSize.width * 3 / 2, 0));
	this->runAction(moveBird);
}
