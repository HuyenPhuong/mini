#include "Skater.h"
#include "Utility/XHelper.h"
#include "Utility/Tags.h"
#include "SimpleAudioEngine.h"
Skater::Skater(){}
Skater::~Skater(){}

Skater* Skater::create(string fileName)
{
	Skater* skater = new Skater();
	skater->init(fileName);
	skater->autorelease();
	return skater;
}

bool Skater::init(string fileName)
{
	if (!Node::init())
		return false;
	this->isDeath = false;
	this->isJumping = false;
	this->isSitting = false;
	this->isDoubleJump = false;
	this->isIncrease = false;
	this->bonusX2 = false;
	this->coin = 0;
	this->score = 0;

	//-------------  Khởi tạo sprite chính -------------
	_sprite = Sprite::create(fileName);
	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprite->setPosition(0, 0);
	this->addChild(_sprite);

	//-------------   Physic Body  --------------
	body = PhysicsBody::createBox(_sprite->getBoundingBox().size, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2(0, 0));
	body->setDynamic(true);
	body->setMass(48.0f);
	body->setAngularVelocityLimit(0.0f);
	body->setRotationEnable(false);
	body->setTag(Tags::SKATER);
	body->setCollisionBitmask(0x02);
	body->setContactTestBitmask(1);
	body->setCategoryBitmask(0x01);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);

	//contact listner
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Skater::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	

	return true;
}

//Animation
void Skater::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation(name, count, time, true, this->_sprite);
}
void Skater::runAnimation_Reserve(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation_Reverse(name, count, time, isRepeat, this->_sprite);
}
void Skater::runAnimation_Run()
{
	runAnimation("play", 3, 0.5f, true);
	this->isSitting = false;
//	this->body = PhysicsBody::createBox(_sprite->getBoundingBox().size, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2(0, 0));
//	this->setPhysicsBody(body);
}
void Skater::runAnimation_Jump()
{
	runAnimation("jump", 5, 0.2f, false);
	this->isSitting = false;
}
void Skater::runAnimation_Fail()
{
	runAnimation("fail", 3, 0.1f, false);
	this->isDeath = true;
	this->isSitting = false;
}
void Skater::runAnimation_Up()
{
	runAnimation_Reserve("down", 3, 0.1f, false);
	this->isSitting = false;
}
void Skater::runAnimation_Between_Up_And_Down()
{
	runAnimation("between_up_and_down", 3 , 0.1f, false);
	this->isSitting = true;
}
void Skater::runAnimation_Down()
{
	runAnimation("down", 3, 0.1f, false);
	this->isSitting = true;
//	body = PhysicsBody::createBox(Size(77,77), PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2(0, 0));
//	this->setPhysicsBody(body);
}
void Skater::jump_Action()
{
	this->body->applyImpulse(Vec2(0, 12000));
	this->isJumping = true;
	this->isDoubleJump = true;
	this->runAnimation_Jump();
	this->runAction(Sequence::create(
		DelayTime::create(1),
		CallFunc::create(CC_CALLBACK_0(Skater::runAnimation_Run, this)),
		nullptr));

	//tạo music
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/beep9.mp3");
}
void Skater::jump_Action_Double()
{
	this->isDoubleJump = false;
	this->body->applyImpulse(Vec2(0, 8500));
	this->runAnimation_Between_Up_And_Down();
	auto rotation = RotateBy::create(0.5, 360);
	this->runAction(rotation);
}
bool Skater::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

//	//----------------   Va chạm vơi chướng ngại vật   ---------
//	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::OBSTRUCTION)
//		|| (a->getTag() == Tags::OBSTRUCTION && b->getTag() == Tags::SKATER))
//	{
//
//			this->isDeath = true;
//			//this->runAnimation_Fail();
//			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Powerup10.wav");
//	}
//
//	//Va chạm với Bird
//	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::BIRD)
//		|| (a->getTag() == Tags::BIRD && b->getTag() == Tags::SKATER))
//	{
//		if (this->isSitting == false)
//		{
//			this->isDeath = true;
//			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Powerup10.wav");
//		}
//
//	}
//
//	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::MAIXE)
//		|| (a->getTag() == Tags::MAIXE && b->getTag() == Tags::SKATER))
//	{
//		this->isJumping = false;
//	}
//
//	//Va cham voi ROAD
//	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::ROAD) || (a->getTag() == Tags::ROAD && b->getTag() == Tags::SKATER))
//	{
//		this->isJumping = false;
//	}
//
//	//Va chạm với COIN
//	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0 || (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0)
//	{
//		if (a != NULL && b != NULL && a->getNode() != NULL && b->getNode() != NULL)
//		{
//			if (a->getTag() == Tags::SKATER && b->getTag() == Tags::COIN)
//			{
//				b->getNode()->removeFromParent();
//				if (bonusX2==true)
//				{
//					this->coin = coin + 2;
//				}
//				else
//					this->coin++;
//
//				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Pickup_Coin3.wav");
//			}
//		}
//
//		if (a != NULL && b != NULL && a->getNode() != NULL && b->getNode() != NULL)
//		{
//			if (b->getTag() == Tags::SKATER && a->getTag() == Tags::COIN)
//			{
//				a->getNode()->removeFromParent();
//				if (bonusX2 == true)
//				{
//					this->coin = coin + 2;
//				}
//				else
//					this->coin++;
//
//				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Pickup_Coin3.wav");
//			}
//		}
//
//		if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::NODE_SCORE) || (b->getTag() == Tags::SKATER && a->getTag() == Tags::NODE_SCORE))
//		{
//			this->score++;
//			this->isIncrease = false;
//
//			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/FinishJump.mp3");
//		}
//
//	}
//
//	//Va chạm với  Bonus X2
//	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::BONUSX2)
//		|| (a->getTag() == Tags::BONUSX2 && b->getTag() == Tags::SKATER))
//	{
//		auto e = a->getTag() == Tags::BONUSX2 ? a : b;
//		e->getNode()->removeFromParent();
//		this->bonusX2 = true;
//	}

//	//Va cham giua Skater vs Battery
//	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::BATTERY)
//		|| (a->getTag() == Tags::BATTERY && b->getTag() == Tags::SKATER))
//	{
//		auto e = a->getTag() == Tags::BATTERY ? a : b;
//		e->getNode()->removeFromParent();
//		if (this->battery < 1.0) battery += 0.25;
//		if (battery > 1.0) battery = 1.0;
//	}

	return true;
}
