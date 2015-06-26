/*
 * PowerSpeed.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Dang
 */

#include "PowerSpeed.h"

Power_Speed::Power_Speed() {
	// TODO Auto-generated constructor stub

}

Power_Speed::~Power_Speed() {
	// TODO Auto-generated destructor stub
}

bool Power_Speed::init()
{
	if (!Node::init()) return false;

	this->sprite = Sprite::create("Power_Speed.png");
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->addChild(sprite);

	return true;
}

Power_Speed * Power_Speed::create_Power_Speed()
{
	Power_Speed * ps = new Power_Speed();
	ps->init();
	ps->autorelease();
	return ps;
}

void Power_Speed::Set_Scale(float scale)
{
	this->sprite->setScaleX(scale);
}
