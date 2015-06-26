#include "Object_Layer.h"
#include "Utility/Config.h"
#include "Utility/Tags.h"
#include "Model/Skater.h"
#include "Model/Coin.h"
#include "Model/Car.h"
#include "Model/Animal.h"
#include "Model/Bird.h"
#include "Model/Coin.h"
#include "Model/Battery.h"
#include "Model/Bonusx2.h"
#include "SimpleAudioEngine.h"
#include <iostream>
using namespace std;
USING_NS_CC;
Object_Layer::Object_Layer()
{
	//Speed
	speed_Obs = 3.5f;
	this->speed_Bird = 14.0f;
//	this->hinhmo = Sprite::create("hinhmo.png");
//	this->fire = Sprite::create("Speed_Skate.png");
}


Object_Layer::~Object_Layer()
{
}

bool Object_Layer::init()
{
	if (!Layer::init()) return false;

	//SkaterKid
	skater = Skater::create("0.png");
	skater->setPosition(Config::centerPoint.x-250, Config::centerPoint.y-150);
	skater->runAnimation_Run();
	this->addChild(skater, 10);

	//Road
	Node * road = Node::create();
	road->setPosition(Config::screenSize.width / 2, Config::screenSize.height / 14);
	road->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	PhysicsBody * body_Road = PhysicsBody::createBox(Size(Config::screenSize.width, Config::screenSize.height / 8), PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	body_Road->setTag(Tags::ROAD);
	body_Road->setDynamic(false);
	body_Road->setContactTestBitmask(1);
	body_Road->setCollisionBitmask(1);
	road->setPhysicsBody(body_Road);
	this->addChild(road);

	//Spawn
	spawnObs = SpawnObs::createSpawnObs();
	spawnObs->setPosition(Point(Config::screenSize.width, Config::screenSize.height / 10.5 + Config::screenSize.height / 9));
//	spawnObs->SinhCar();
//	spawnObs->SinhAni();
//	spawnObs->SinhBird();
	spawnObs->Random_Spawn();
	this->addChild(spawnObs);

	return true;
}

Object_Layer * Object_Layer::create_Object_Layer()
{
	Object_Layer * layer = new Object_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}

void Object_Layer::SetPhysicsWorld(PhysicsWorld * world)
{
	this->physicsWorld = world;
}

void Object_Layer::Spawn_Car(float dt)
{
	int i = random(1, 3);
	char name[100];
	sprintf(name, "Obtruction/car%i.png", i);
	Car * car = Car::create(name);
	car->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto randomDis = random(0.5, 2.0);
	car->MoveCar(randomDis*5, randomDis);
	car->setPosition(Point(Config::screenSize.width + randomDis*Config::screenSize.width, Config::screenSize.height / 10.5 + Config::screenSize.height / 9));
	this->addChild(car);

	//tạo music
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/bus.mp3");
}

void Object_Layer::Spawn_Animal(float dt)
{

	Animal * ani = Animal::create("0.png");
	ani->setScale(0.7);
	int k = cocos2d::random(1, 4);
	switch (k)
	{
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
	ani->setPosition(Point(Config::screenSize.width, Config::screenSize.height / 10.5 + Config::screenSize.height / 9));
	auto moveAni = MoveBy::create(6, Vec2(-Config::screenSize.width * 3 / 2, 0));
	this->addChild(ani);
	ani->runAction(moveAni);
}

void Object_Layer::Spawn_Coin(float dt)
{

	int min = 1.0;
	int max = 8.0;
	int rangeDuration = max - min;
	int randomDuration = (rand() % rangeDuration) + min;

	int k = cocos2d::random(1, 2);

	for (int i = 0; i < randomDuration; i++)
	{
		auto obs = Coin::create("0.png");
		obs->setScale(0.3);
		obs->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		obs->setPosition(Point(Config::screenSize.width + 40 * i, Config::screenSize.height / 2));
		auto moveObs = MoveBy::create(6, Vec2(-Config::screenSize.width * 3 / 2, 0));
		switch (k)
		{
		case 1:
			obs->runAnimation("coin", 7, 0.8f, true);
			break;
		case 2: 
			obs->runAnimation("coin2", 7, 0.8f, true); 
			break;
		}
		this->addChild(obs);
		obs->runAction(moveObs);
	}
}

//void Object_Layer::Spawn_Obstruction2(float dt)
//{
//	std::vector<std::string> _spriteNames = { "Obtruction/1.png", "Obtruction/2.png", "Obtruction/3.png", "Obtruction/4.png", "Obtruction/5.png" };
//	int k = cocos2d::random(0, 4);
//	auto foo = Animal::create(_spriteNames.at(k));
//	foo->setPosition(Point(Config::screenSize.width, Config::screenSize.height / 10.5 + Config::screenSize.height / 9));
//	foo->setScale(0.6);
//	addChild(foo, 1);
//	auto moveObs = MoveBy::create(7, Vec2(-Config::screenSize.width * 3 / 2, 0));
//	foo->runAction(moveObs);
//}

void Object_Layer::Spawn_Bonusx2(float dt)
{
	Bonusx2 * bonus = Bonusx2::create("Bonus/2x.png");
	bonus->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bonus->setPosition(Point(Config::screenSize.width + 40, Config::screenSize.height / 2));
	addChild(bonus, 1);
	auto moveObs = MoveBy::create(6, Vec2(-Config::screenSize.width * 3 / 2, 0));
	bonus->runAction(moveObs);

	////cho 10s 
	this->runAction(Sequence::create(
		DelayTime::create(10),
		nullptr));
	skater->bonusX2 = false;
}

void Object_Layer::Spawn_Bird(float dt)
{
	Bird * bird = Bird::create("bird.png");
	bird->setPosition(Point(Config::screenSize.width, Config::centerPoint.y-80));
	bird->setScale(0.3f);
	bird->runAnimation("bird", 4, 0.1f, true);
	addChild(bird, 1);
//	bird->MoveBird(this->speed_Bird);
//	auto moveObs = MoveBy::create(6, Vec2(-Config::screenSize.width * 3 / 2, 0));
//	bird->runAction(moveObs);
}

void Object_Layer::Show_SpeedUp()
{
	this->hinhmo = Sprite::create("hinhmo.png");
	hinhmo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	hinhmo->setPosition(Config::centerPoint);
	hinhmo->setOpacity(192);
	hinhmo->setScale(Config::getScale(hinhmo));
	this->addChild(hinhmo, 9);

	this->fire = Sprite::create("Speed_Skate.png");
	fire->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	fire->setScale(0.5f);
	fire->setPosition(Point(- this->skater->_sprite->getContentSize().width/4.5, - this->skater->_sprite->getContentSize().height/3));
	this->skater->addChild(fire);
}

void Object_Layer::Spawn_Battery(float dt)
{
	Battery * bat = Battery::create_Battery();
	bat->setPosition(Point(Config::screenSize.width, Config::centerPoint.y-80));
	bat->setScale(0.3f);
	bat->MoveBattery(15);
	addChild(bat, 1);
}
