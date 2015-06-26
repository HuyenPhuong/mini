/*
 * SpawnObs.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: Dang
 */

#include "SpawnObs.h"
#include "Model/Car.h"
#include "Model/Bird.h"
#include "Model/Animal.h"
#include "Utility/Config.h"
#include "Model/Battery.h"
#include <iostream>
using namespace std;

SpawnObs::SpawnObs() {
	// TODO Auto-generated constructor stub
	this->isGenerate = true;
	this->speed_Animal = 16.0f;
	this->speed_Car = 20.0f;
	this->speed_Bird = 16.0f;
	this->speed_Animal_2 = 26.0f;
	this->speed_Car_2 = 32.0f;
	this->speed_Bird_2 = 26.0f;
	this->speed_Battery = 13.0f;
	this->max_Random = 8;
}

SpawnObs::~SpawnObs() {
	// TODO Auto-generated destructor stub
}

SpawnObs * SpawnObs::createSpawnObs()
{
	SpawnObs * sObs = new SpawnObs();
	sObs->init();
	sObs->autorelease();
	return sObs;
}

void SpawnObs::SinhCar(float speed)
{
	if (this->isGenerate)
	{
		int i = random(1, 3);
		char name[100];
		sprintf(name, "Obtruction/car%i.png", i);
		Car * car = Car::create(name);
		car->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		car->MoveCar(speed);
		this->addChild(car);

//		auto sinh = CallFunc::create(CC_CALLBACK_0(SpawnObs::SinhCar, this));
//		auto delay = DelayTime::create(random(10, 20));
//		this->runAction(Sequence::createWithTwoActions(delay, sinh));
	}
}

void SpawnObs::SinhAni(float speed)
{
	if (isGenerate)
	{
		auto ani = Animal::create("0.png");
		ani->setScale(0.7);
		int k = cocos2d::random(1, 4);
		switch (k) {
		case 1:
			ani->runAnimation("dog", 4, 0.5f, true);
			break;
		case 2:
			ani->runAnimation("chick", 4, 0.5f, true);
			break;
		case 3:
			ani->runAnimation("cat", 4, 0.5f, true);
			break;
		case 4:
			ani->runAnimation("hour", 4, 0.5f, true);
			break;
		}
		ani->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		ani->MoveAnimal(speed);
		this->addChild(ani);

//		auto sinh = CallFunc::create(CC_CALLBACK_0(SpawnObs::SinhAni, this));
//		auto delay = DelayTime::create(random(5, 15));
//		this->runAction(Sequence::createWithTwoActions(delay, sinh));
	}
}

void SpawnObs::SinhBird(float speed)
{
	if (this->isGenerate)
	{
		Bird * bird = Bird::create("bird.png");
		bird->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		bird->MoveBird(speed);
		bird->setScale(0.3);
		bird->setPosition(Point(0, Config::centerPoint.y/4));
		bird->runAnimation("bird", 4, 0.1f, true);
		this->addChild(bird);

//		auto sinh = CallFunc::create(CC_CALLBACK_0(SpawnObs::SinhBird, this));
//		auto delay = DelayTime::create(random(8, 12));
//		this->runAction(Sequence::createWithTwoActions(delay, sinh));
	}
}

void SpawnObs::SinhBattery()
{
	Battery * bat = Battery::create_Battery();
	bat->setPosition(Point(0, Config::centerPoint.y/4));
	bat->setScale(0.3f);
	bat->MoveBattery(this->speed_Battery);
	this->addChild(bat, 1);

	auto sinh = CallFunc::create(CC_CALLBACK_0(SpawnObs::SinhBattery, this));
	auto delay = DelayTime::create(random(2, 4));
	this->runAction(Sequence::createWithTwoActions(delay, sinh));
}

void SpawnObs::Random_Spawn()
{
	if (isGenerate)
	{
		int k = cocos2d::random(1, 3);
		switch (k)
		{
			case 1:
				SinhAni(this->speed_Animal);
				break;
			case 2:
				SinhCar(this->speed_Car);
				break;
			case 3:
				SinhBird(this->speed_Bird);
				break;
		}

		auto sinh = CallFuncN::create(CC_CALLBACK_0(SpawnObs::Random_Spawn, this));
		auto delay = DelayTime::create(random(1, this->max_Random));
		this->runAction(Sequence::createWithTwoActions(delay, sinh));
	}
}

void SpawnObs::SpeedUp_Spawn()
{
	if (!isGenerate)
	{
		int k = cocos2d::random(1, 3);
		switch (k)
		{
			case 1:
				SinhAni(this->speed_Animal_2);
				break;
			case 2:
				SinhCar(this->speed_Car_2);
				break;
			case 3:
				SinhBird(this->speed_Bird_2);
			break;
		}

		auto sinh = CallFuncN::create(CC_CALLBACK_0(SpawnObs::SpeedUp_Spawn, this));
		auto delay = DelayTime::create(random(1, 8));
		this->runAction(Sequence::createWithTwoActions(delay, sinh));
	}
}
