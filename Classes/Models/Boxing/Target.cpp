#include "Target.h"
#include "Utility/Config.h"
#include "Utility/Tags.h"
#include "Utility/XHelper.h"
using namespace cocos2d;

Target::Target(){}
Target::~Target(){}


Target* Target::create(string fileName)
{
	Target* head = new Target();
	head->init(fileName);
	head->autorelease();
	return head;
}

bool Target::init(string fileName)
{
	if (!Node::init())
		return false;

	//-------------  Khởi tạo sprite chính -------------
	_sprite = Sprite::create(fileName);
	_sprite->setPosition(0, 0);
	this->addChild(_sprite);

	/*
	//-------------   Physic Body  --------------
	body = PhysicsBody::createBox(_sprite->getBoundingBox().size, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2(0, 0));
	body->setGravityEnable(false);
	body->setDynamic(true);
	body->setTag(Tags::TARGET);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);
	*/
	return true;
}

void Target::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation2(name, count, time, true, this->_sprite);
}