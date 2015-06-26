#include "Animal.h"
#include "Utility/Tags.h"
#include "Utility/Config.h"
#include "Utility/XHelper.h"

Animal::Animal(){}
Animal::~Animal(){}

Animal* Animal::create(string fileName)
{
	Animal* animal = new Animal();
	animal->init(fileName);
	animal->autorelease();
	return animal;
}

bool Animal::init(string fileName)
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
	body->setTag(Tags::OBSTRUCTION);
	body->setCollisionBitmask(0x02);
	body->setContactTestBitmask(1);
	body->setCategoryBitmask(0x01);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);

	//Score
	auto nodeScore = Node::create();
	nodeScore->setPosition(_sprite->getContentSize().width * 2.1 / 4, Config::screenSize.height/2 /*_sprite->getContentSize().height * 2.3 / 3*/);
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
void Animal::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation(name, count, time, true, this->_sprite);
}

void Animal::MoveAnimal(float speed)
{
	auto moveAni = MoveBy::create(100/speed, Vec2(-Config::screenSize.width * 3 / 2, 0));
	this->runAction(moveAni);
}
