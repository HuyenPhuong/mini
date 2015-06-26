#include "GamePlay.h"
#include "Model/Skater.h"
#include "View/Object_Layer.h"
#include "Model/Car.h"
#include "Model/Bird.h"
#include "Model/Battery.h"
#include "Utility/Tags.h"
#include "View/Start_Scene.h"
#include "View/End_Scene.h"
#include "SimpleAudioEngine.h"
#include <sstream>
#include "Utility/Config.h"
using namespace std;

GamePlay::GamePlay() {
	this->sosanh = 1;
	this->isSpeedUp = true; //True la dc phep Speed Up
	this->isSpeeding = false;
	this->isRemoved = false;
	this->current_Speed_Scoll_Background = 0;
	this->current_Speed_Animal = 0;
	this->current_Speed_Car = 0;
	this->setKeypadEnabled(true);
	this->setKeyboardEnabled(true);
}

GamePlay::~GamePlay() {
}

bool GamePlay::init() {
	if (!Layer::init())
		return false;

	//Best Score
	bestScore = 0;

//	//Back button
//	this->setKeypadEnabled(true);
//	this->setKeyboardEnabled(true);

	//Xử lý Touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//Jump Button
	jump_Button = Button::create("Button/Jump_Button.png",
			"Button/Jump_Button_Selected.png",
			"Button/Jump_Button_Selected.png");
	jump_Button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	jump_Button->setOpacity(128);
	jump_Button->setScale(0.6);
	jump_Button->setPosition(
			Point(Config::screenSize.width,
					jump_Button->getContentSize().width / 2));
	jump_Button->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {
				switch (type)
				{
					case ui::Widget::TouchEventType::BEGAN:
					if (object_Layer->skater->isDeath == false && object_Layer->skater->isJumping == false)
					{
						object_Layer->skater->jump_Action();
					}
					else if (object_Layer->skater->isDeath == false && object_Layer->skater->isJumping == true && object_Layer->skater->isDoubleJump == true)
					{
						object_Layer->skater->jump_Action_Double();
					}
					break;
					case ui::Widget::TouchEventType::ENDED:
					break;
					default:
					break;
				}
			});
	this->addChild(jump_Button);

	//Lower Button
	lower_Button = Button::create("Button/Lower_Button.png",
			"Button/Lower_Button_Selected.png",
			"Button/Lower_Button_Selected.png");
	lower_Button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	lower_Button->setOpacity(128);
	lower_Button->setScale(0.6);
	lower_Button->setPosition(
			Point(
					Config::screenSize.width
							- lower_Button->getContentSize().width / 2, 0));
	lower_Button->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {
				switch (type)
				{
					case ui::Widget::TouchEventType::BEGAN:
					object_Layer->skater->runAnimation_Down();
					break;
					case ui::Widget::TouchEventType::MOVED:
					object_Layer->skater->runAnimation_Between_Up_And_Down();
					break;
					case ui::Widget::TouchEventType::ENDED:
					object_Layer->skater->runAnimation_Up();
					object_Layer->skater->runAnimation_Run();
					break;
					default:
					break;
				}
			});
	this->addChild(lower_Button);

	//Speed Button
	speed_Button = Button::create("Button/Speed_Button.png",
			"Button/Speed_Button_Selected.png",
			"Button/Speed_Button_Selected.png");
	speed_Button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	speed_Button->setOpacity(128);
	speed_Button->setScale(0.6);
	speed_Button->setPosition(Point(0, 0));
	speed_Button->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {
				switch (type)
				{
					case ui::Widget::TouchEventType::BEGAN:
					if (this->isSpeedUp == true)
					{
						this->isSpeeding = true;
						SpeedUp();
					}
					break;
					case ui::Widget::TouchEventType::ENDED:
					break;
					default:
					break;
				}
			});
	this->addChild(speed_Button);

//	this->schedule(schedule_selector(Object_Layer::Spawn_Bonusx2), 20);
//	this->schedule(schedule_selector(Object_Layer::Spawn_Bird), 20);
//	this->schedule(schedule_selector(Object_Layer::Spawn_Car), 8);
	this->schedule(schedule_selector(Object_Layer::Spawn_Coin), 12);
//	this->schedule(schedule_selector(Object_Layer::Spawn_Animal), 5);
//	this->schedule(schedule_selector(Object_Layer::Spawn_Obstruction2), 16);
	this->schedule(schedule_selector(Object_Layer::Spawn_Battery), 15);
	this->scheduleUpdate();

	//contact listner
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlay::onContactBegin,
			this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,
			this);

	return true;
}

GamePlay * GamePlay::createGamePlayLayer() {
	GamePlay * layer = new GamePlay();
	layer->init();
	layer->autorelease();
	return layer;
}

bool GamePlay::onTouchBegan(Touch *touch, Event *unused_event) {
	if (object_Layer->skater->isDeath == false
			&& object_Layer->skater->isJumping == false) {
		object_Layer->skater->jump_Action();
	}
	return true;
}

bool GamePlay::onContactBegin(PhysicsContact &contact) {
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	//Va cham giua Skater vs Battery
	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::BATTERY)
			|| (a->getTag() == Tags::BATTERY && b->getTag() == Tags::SKATER)) {
		if (object_Layer->skater->isSitting == false) {
			auto e = a->getTag() == Tags::BATTERY ? a : b;
			e->getNode()->removeFromParent();
			if (score_Layer->heso_Scale < 1.0)
				score_Layer->heso_Scale += 0.25;
			if (score_Layer->heso_Scale > 1.0)
				score_Layer->heso_Scale = 1.0;
			score_Layer->UpdatePower();
		}

	}

	//----------------   Va chạm Skater vơi chướng ngại vật   ---------
	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::OBSTRUCTION)
			|| (a->getTag() == Tags::OBSTRUCTION && b->getTag() == Tags::SKATER))
	{
		if (this->isSpeeding == false)
		{
			object_Layer->skater->isDeath = true;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Powerup10.wav");
		}
		else if (this->isSpeeding == true)
		{
			auto e = a->getTag() == Tags::OBSTRUCTION ? a : b;
			e->getNode()->removeFromParent();
		}

	}

	//Va chạm với Bird
	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::BIRD)
			|| (a->getTag() == Tags::BIRD && b->getTag() == Tags::SKATER))
	{
		if (object_Layer->skater->isSitting == false && this->isSpeeding == false)
		{
			object_Layer->skater->isDeath = true;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Powerup10.wav");
		}
		else if (this->isSpeeding == true)
		{
			auto e = a->getTag() == Tags::BIRD ? a : b;
			e->getNode()->removeFromParent();
		}
	}

	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::MAIXE) || (a->getTag() == Tags::MAIXE && b->getTag() == Tags::SKATER))
	{
		if (this->isSpeeding == false)
		{
			object_Layer->skater->isJumping = false;
		}
		else if (this->isSpeeding == true)
		{
			auto e = a->getTag() == Tags::MAIXE ? a : b;
			e->getNode()->removeFromParent();
		}
	}

	//Va cham voi ROAD
	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::ROAD)
			|| (a->getTag() == Tags::ROAD && b->getTag() == Tags::SKATER)) {
		object_Layer->skater->isJumping = false;
	}

	//Va chạm với COIN
	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0
			|| (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0) {
		if (a != NULL && b != NULL && a->getNode() != NULL
				&& b->getNode() != NULL) {
			if (a->getTag() == Tags::SKATER && b->getTag() == Tags::COIN) {
				b->getNode()->removeFromParent();
				if (object_Layer->skater->bonusX2 == true) {
					object_Layer->skater->coin += 2;
				} else
					object_Layer->skater->coin++;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
						"Sound/Pickup_Coin3.wav");
			}
		}

		if (a != NULL && b != NULL && a->getNode() != NULL
				&& b->getNode() != NULL) {
			if (b->getTag() == Tags::SKATER && a->getTag() == Tags::COIN) {
				a->getNode()->removeFromParent();
				if (object_Layer->skater->bonusX2 == true) {
					object_Layer->skater->coin += 2;
				} else
					object_Layer->skater->coin++;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
						"Sound/Pickup_Coin3.wav");
			}
		}

		if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::NODE_SCORE)
				|| (b->getTag() == Tags::SKATER
						&& a->getTag() == Tags::NODE_SCORE)) {
			object_Layer->skater->score++;
			object_Layer->skater->isIncrease = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
					"Sound/FinishJump.mp3");
		}
	}

	//Va chạm với  Bonus X2
	if ((a->getTag() == Tags::SKATER && b->getTag() == Tags::BONUSX2)
			|| (a->getTag() == Tags::BONUSX2 && b->getTag() == Tags::SKATER)) {
		auto e = a->getTag() == Tags::BONUSX2 ? a : b;
		e->getNode()->removeFromParent();
		object_Layer->skater->bonusX2 = true;
	}
	return true;

}

void GamePlay::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
		cocos2d::Event *event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		auto scene = Start_Scene::create_Start_Scene();
		Director::getInstance()->replaceScene(
				TransitionFade::create(0.5, scene, Color3B::WHITE));
	}
}

void GamePlay::Set_Object_Layer(Object_Layer * layer) {
	this->object_Layer = layer;
}

void GamePlay::Set_Score_Layer(Score_Layer * layer) {
	this->score_Layer = layer;
}

void GamePlay::Set_Background_Layer(Background_Layer * layer) {
	this->background_Layer = layer;
}

void GamePlay::SpeedUp()
{
	object_Layer->Show_SpeedUp();
	this->current_Speed_Scoll_Background = background_Layer->speed_Scroll;
	this->background_Layer->speed_Scroll = 2500;
//	this->object_Layer->spawnObs->speed_Animal = 35;
//	this->object_Layer->spawnObs->speed_Bird = 35;
//	this->object_Layer->spawnObs->speed_Car = 40;
	this->object_Layer->spawnObs->speed_Battery = 50;
	this->isSpeedUp = false;
	this->isRemoved = false;
}

void GamePlay::UpdateSpeed()
{

}

void GamePlay::update(float dt) {
	if (object_Layer->skater->isDeath == true) {
		//Dừng sinh Oject và cuộn background
		background_Layer->speed_Scroll = 0;
		this->unschedule(schedule_selector(Object_Layer::Spawn_Car));
		this->unschedule(schedule_selector(Object_Layer::Spawn_Coin));
		this->unschedule(schedule_selector(Object_Layer::Spawn_Animal));
		this->object_Layer->spawnObs->isGenerate = false;

		//Lưu Highscore
		bestScore = UserDefault::getInstance()->getIntegerForKey("BESTSCORE");
		if (this->object_Layer->skater->score > bestScore) {
			UserDefault::getInstance()->setIntegerForKey("BESTSCORE",
					this->object_Layer->skater->score);
		}

		//Chuyển scene
		auto endScene = End_Scene::create_End_Scene(this->object_Layer->skater->score);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, endScene));
	}

	//Tăng speed cuộn background và speed di chuyển của Obs
	if ((this->object_Layer->skater->score % this->sosanh) == 0 && this->object_Layer->skater->isIncrease == false)
	{
		background_Layer->speed_Scroll += 30;
		current_Speed_Scoll_Background += 30;
		current_Speed_Animal += 0.4;
		current_Speed_Car += 0.8;
		object_Layer->spawnObs->speed_Animal += 1.0;
		object_Layer->spawnObs->speed_Car += 1.0;
		object_Layer->spawnObs->speed_Bird += 1.0;

		this->object_Layer->skater->isIncrease = true;
		this->sosanh++;
	}

	//Speed
	if (this->isSpeeding == true && score_Layer->heso_Scale > 0.02f) //Dang speedUp
	{
		score_Layer->heso_Scale -= dt / 5;
		score_Layer->power_bar->Set_Scale(score_Layer->heso_Scale);
		object_Layer->spawnObs->max_Random = 1;
//		object_Layer->spawnObs->SpeedUp_Spawn();
	}
	if (score_Layer->heso_Scale <= 0.02f) //Het luc
	{
		this->isSpeedUp = false;
		this->isSpeeding = false;
	}
	if (this->isSpeedUp == false && this->isSpeeding == false && this->isRemoved == false) //Sau khi SpeedUp xong
	{
		object_Layer->spawnObs->max_Random = 8; //Thoi gian sinh Obs
		object_Layer->skater->battery = 0.02f;
//		score_Layer->heso_Scale = object_Layer->skater->battery;
		object_Layer->fire->removeFromParent();
		object_Layer->hinhmo->removeFromParent();
		background_Layer->speed_Scroll = this->current_Speed_Scoll_Background;
//		object_Layer->spawnObs->speed_Animal = this->current_Speed_Animal;
//		object_Layer->spawnObs->speed_Bird = this->current_Speed_Animal;
//		object_Layer->spawnObs->speed_Car = this->current_Speed_Car;
		this->isRemoved = true;
	}
	if (score_Layer->heso_Scale <= 0.02f) //Co luc
	{
		this->isSpeedUp = true;
	}

	//Coin
	stringstream ss;
	ss << this->object_Layer->skater->coin;
	this->score_Layer->coin->setString(ss.str());

	//Score
	stringstream ss1;
	ss1 << this->object_Layer->skater->score;
	this->score_Layer->current_Score->setString(ss1.str());
}

