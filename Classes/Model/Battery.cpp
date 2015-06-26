/*
 * Battery.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: Dang
 */

#include "Battery.h"
#include "Utility/Config.h"
#include "Utility/Tags.h"

Battery::Battery() {
	// TODO Auto-generated constructor stub

}

Battery::~Battery() {
	// TODO Auto-generated destructor stub
}

bool Battery::init()
{
	if (!Node::init()) return false;

	this->sprite = Sprite::create("Battery.png");
	this->sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(sprite);

	body = PhysicsBody::createBox(sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	body->setDynamic(false);
	body->setTag(Tags::BATTERY);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(1);
	body->setCollisionBitmask(0x02);
	this->setPhysicsBody(body);
	this->setScale(0.5f);


	return true;
}

Battery * Battery::create_Battery()
{
	Battery * bat = new Battery();
	bat->init();
	bat->autorelease();
	return bat;
}

void Battery::MoveBattery(float speed)
{
	auto moveBat = MoveBy::create(100/speed, Vec2(- Config::screenSize.width * 3 / 2, 0));
	this->runAction(moveBat);
}
