#include "Car.h"
#include "Utility/XHelper.h"
#include "Utility/Tags.h"
#include "Utility/Config.h"

Car::Car()
{
	this->speed_Obs = 6.0f;
}

Car::~Car(){}

Car* Car::create(string fileName)
{
	Car* car = new Car();
	car->init(fileName);
	car->autorelease();
	return car;
}

bool Car::init(string fileName)
{
	if (!Node::init())
		return false;

	//-------------  Khởi tạo sprite chính -------------
	_sprite = Sprite::create(fileName);
	_sprite->setPosition(0, 0);
	_sprite->setAnchorPoint(Vec2(0.25, 0.25));
	this->addChild(_sprite);

	
	//-------------   Physic Body  --------------
	body = PhysicsBody::createBox(Size(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2), PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
	body->setDynamic(false);
	body->setTag(Tags::OBSTRUCTION);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);


	//Mai xe
	auto nodeCar = Node::create();
	nodeCar->setPosition(_sprite->getContentSize().width * 2.1 / 4, _sprite->getContentSize().height * 2.3 / 3);
	nodeCar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprite->addChild(nodeCar);
	PhysicsBody * bodyNodeCar = PhysicsBody::createBox(Size(_sprite->getContentSize().width * 2.5 / 5, _sprite->getContentSize().height / 3), PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
	bodyNodeCar->setTag(Tags::MAIXE);
	bodyNodeCar->setDynamic(false);
	bodyNodeCar->setContactTestBitmask(1);
	bodyNodeCar->setCollisionBitmask(1);
	nodeCar->setPhysicsBody(bodyNodeCar);

	//Score
	auto nodeScore = Node::create();
	nodeScore->setPosition(_sprite->getContentSize().width * 2.1 / 4, _sprite->getContentSize().height);
	nodeScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprite->addChild(nodeScore);
	PhysicsBody * bodyNodeScore = PhysicsBody::createBox(Size(_sprite->getContentSize().width * 2.5 / 5, Config::screenSize.height), PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2::ZERO);
	bodyNodeScore->setTag(Tags::NODE_SCORE);
	bodyNodeScore->setDynamic(false);
	bodyNodeScore->setCategoryBitmask(0x01);
	bodyNodeScore->setContactTestBitmask(1);
	bodyNodeScore->setCollisionBitmask(0x02);
	nodeScore->setPhysicsBody(bodyNodeScore);

	return true;
}
//Animation
void Car::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation(name, count, time, true, this->_sprite);
}

void Car::MoveCar(float speed, float distance)
{
	auto moveObs = MoveTo::create(speed, Vec2(-(distance + 2)*Config::screenSize.width, 0));
	this->runAction(moveObs);
}

void Car::MoveCar(float speed)
{
	auto moveObs = MoveTo::create(100/speed, Vec2(-Config::screenSize.width * 3 / 2, 0));
	this->runAction(moveObs);
}
