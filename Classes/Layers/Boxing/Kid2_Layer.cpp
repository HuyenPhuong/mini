#include "Kid2_Layer.h"
#include "Models\Boxing\Kid.h"
#include "Models\Boxing\Target.h"
#include "Utility\Config.h"
#include "Utility\Tags.h"
#include "Utility\XHelper.h"
#include "Control\Boxing\Controller.h"


using namespace std;
Kid* kid1;
Kid* kid2;
Kid *kid3;
Kid *kid4;
Kid *kid5;
Target *target;

Kid_Layer::Kid_Layer()
{
}


Kid_Layer::~Kid_Layer()
{
}

bool Kid_Layer::init()
{

	if (!Layer::init()) return false;

	//kid sprite
	kid1 = Kid::create("Boxing/face11.png");
	kid1->moveAction();
	this->addChild(kid1, 1);

	
	kid2 = Kid::create("Boxing/face21.png");
	kid2->moveAction();
	this->addChild(kid2, 1);


	kid3 = Kid::create("Boxing/face31.png");
	kid3->moveAction();
	this->addChild(kid3, 1);

	kid4 = Kid::create("Boxing/face41.png");
	kid4->moveAction();
	this->addChild(kid4, 1);

	kid5 = Kid::create("Boxing/face51.png");
	kid5->moveAction();
	this->addChild(kid5, 1);

	//target sprite
	target = Target::create("Boxing/boxing1.png");
	target->setPosition(Config::centerPoint);
	target->setScale(0.7);
	this->addChild(target, 2);
	
	
	auto event_listener = EventListenerTouchAllAtOnce::create();
	event_listener->onTouchesEnded = [=](const std::vector<Touch*>& pTouches, Event* event){
	auto touch = *pTouches.begin();
	auto openGl_location = touch->getLocation();
	auto move_action = MoveTo::create(0.0f, openGl_location);
	
	target->runAction(move_action);
	

	CCLOG("%.1f %.1f", target->getPositionX(), target->getPositionY());
	target->runAnimation("boxing", 3, 0.08f, false);
	

	if (XHelper::checkShoot(kid1->getPosition(), 50, openGl_location))
	{
		kid1->runAnimation("face1", 3, 1.0f, false);
		Controller_Layer::trungRoi();
		CCLOG("%.1f %.1f", kid1->getPositionX(), kid1->getPositionY());
	}

	else if (XHelper::checkShoot(kid2->getPosition(), 50, openGl_location))
	{
		kid2->runAnimation("face2", 3, 1.0f, false);
		Controller_Layer::trungRoi();
		CCLOG("2");

	}
	else if (XHelper::checkShoot(kid3->getPosition(), 50, openGl_location))
	{
		kid3->runAnimation("face3", 3, 1.0f, false);
		Controller_Layer::trungRoi();
		CCLOG("3");
	}
	else if (XHelper::checkShoot(kid4->getPosition(), 50, openGl_location))
	{
		kid4->runAnimation("face4", 3, 1.0f, false);
		Controller_Layer::trungRoi();
		CCLOG("4");
	}
	else if (XHelper::checkShoot(kid5->getPosition(), 50, openGl_location))
	{
		kid5->runAnimation("face5", 3, 1.0f, false);
		Controller_Layer::trungRoi();
		CCLOG("5");
	}
	else
	{
		Controller_Layer::truotRoi();
	}

	};
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event_listener, target);
	return true;
}

Kid_Layer * Kid_Layer::create_Kid_Layer()
{
	Kid_Layer * layer = new Kid_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}

void Kid_Layer::SetPhysicsWorld(PhysicsWorld *world)
{
	this->physicsWorld = world;
}

void Kid_Layer::gameOver()
{
	target->setScale(0);
	
}