#include "Kid.h"
#include "Utility/Config.h"
#include "Utility/Tags.h"
#include "Utility/XHelper.h"
using namespace cocos2d;

Kid::Kid(){}
Kid::~Kid(){}

int actualY;

Kid* Kid::create(string fileName)
{
	Kid* head = new Kid();
	head->init(fileName);
	head->autorelease();
	return head;
}

bool Kid::init(string fileName)
{
	if (!Node::init())
		return false;
	isAlive = true;

	//-------------  Khởi tạo sprite chính -------------
	_sprite = Sprite::create(fileName);
	_sprite->setPosition(0, 0);
	_sprite->setScale(1.2);
	this->addChild(_sprite);

	//-------------   Physic Body  --------------
	body = PhysicsBody::createBox(_sprite->getBoundingBox().size, PhysicsMaterial(100.0f, 0.0f, 100.0f), Vec2(0, 0));
	body->setGravityEnable(false);
	body->setDynamic(true);
	body->setTag(Tags::KID);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPhysicsBody(body);

	/*
	//contact listner
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Kid::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/
	return true;
}

Vec2 Kid::randomPotision()
{
	auto kidSize = this->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int minY = kidSize.height / 2;
	int maxY = winSize.height - kidSize.height / 2 ;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) -50 ;

	int minX = kidSize.width / 2;
	int maxX = winSize.width - kidSize.width / 2;
	int rangeX = maxX - minX;
	int randomX = (rand() % rangeX) -50;
	return Vec2(randomX, randomY);
}

void Kid::moveAction()
{
	
	int minDuration = 1.0;
	int maxDuration = 4.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	this->setPosition(randomPotision());
	auto actionMove = MoveTo::create(randomDuration, randomPotision());
	auto actionMove2 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove3 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove4 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove5 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove6 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove7 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove8 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove9 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove10 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove11 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove12 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove13 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove14 = MoveTo::create(randomDuration, randomPotision());
	auto actionMove15 = MoveTo::create(randomDuration, randomPotision());
	this->runAction(CCRepeatForever::create(Sequence::create(actionMove, actionMove2, actionMove3, actionMove4,
		actionMove5, actionMove6, actionMove7, actionMove8, actionMove9, actionMove10, actionMove11,
		actionMove12, actionMove13, actionMove14, actionMove15,nullptr)));
}

/*bool Kid::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();


	//----------------   Va chạm vơi chướng ngại vật   ---------
	if (a != NULL && b != NULL && a->getNode() != NULL && b->getNode() != NULL)
	{
		if ((a->getTag() == Tags::KID && b->getTag() == Tags::TARGET)
			|| (a->getTag() == Tags::TARGET && b->getTag() == Tags::KID))
		{
			log("Noooooooooo");
			isAlive = false;
			auto e = a->getTag() == Tags::KID ? a : b;
			e->getNode()->removeFromParent();
			//PhiTieuLayer::instance->matMau();
		}
	}

	return false;
}
*/

void Kid::runAnimation(string name, int count, float time, bool isRepeat)
{
	XHelper::runAnimation2(name, count, time, true, this->_sprite);
}