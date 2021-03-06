﻿#include "PhiTieuHUDLayer.h"
#include "Utility/Config.h"
#include "Scenes/PhiTieu/PhiTieuScene.h"
#include "Models/PhiTieu/Item.h"
#include "SimpleAudioEngine.h"
#include <sstream>

PhiTieuHUDLayer* PhiTieuHUDLayer::Instance = nullptr;
PhiTieuHUDLayer::PhiTieuHUDLayer() {
}
PhiTieuHUDLayer::~PhiTieuHUDLayer() {
}

void PhiTieuHUDLayer::setPhiTieuLayer(PhiTieuLayer* p) {
	_phiTieuLayer = p;
}

bool PhiTieuHUDLayer::init() {
	if (!Layer::init())
		return false;
	highScore = UserDefault::getInstance()->getIntegerForKey("score4");
	stringstream ss;
	ss<<"Highscore: " << highScore;
	auto txtDiem = Label::createWithTTF(ss.str(), "fonts/Karate.ttf", 30);
	txtDiem->setAnchorPoint(Vec2(0,1));
	txtDiem->setPosition(10, Config::screenSize.height -10 );
	this->addChild(txtDiem);

	//------------------ Music Background -----------------//
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
			"Sound_PhiTieu/Music1.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			"Sound_PhiTieu/Music1.mp3", true);

	//------------------ Button jump  ---------------------
	bt_jump = Button::create("PhiTieu/bt_jump_1.png", "PhiTieu/bt_jump_2.png", "PhiTieu/bt_jump_2.png");
	bt_jump->setAnchorPoint(Vec2(0, 0));
	bt_jump->setPosition(Vec2(20, 20));
	bt_jump->setScale(0.25f);
	bt_jump->addTouchEventListener(this,
			toucheventselector(PhiTieuHUDLayer::click_Jump));
	this->addChild(bt_jump);

	//-----------------  Touch event ------------
	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(
			PhiTieuHUDLayer::touch_PhongTieu, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,
			this);

	//-------------- Trai tim ---------
	for (int i = 0; i < 3; i++) {
		hearts.pushBack(Item::getHeart(i+1));
		this->addChild(hearts.at(i));
	}
	//Tao thanh power


	power = Power::createPower(PhiTieuScene::GetLevel());
	power->setPosition(Vec2(10, Config::screenSize.height - 70));
	power->setScaleY(0.8f);
	this->addChild(power);
	

	//------------------------ Label ---------------------------
	txt_score = Label::createWithTTF("0", "fonts/Karate.ttf", 37);
	txt_score->setPosition(Vec2(Config::screenSize.width - 30,Config::screenSize.height - 27));
	this->addChild(txt_score);

	//-------------------- GAME over --------------------
	Vector<MenuItem*> items;
	mBack = MenuItemLabel::create(Label::createWithTTF("BACK", "fonts/Karate.ttf", 37),CC_CALLBACK_1(PhiTieuHUDLayer::ClickBack, this));
	mBack->setPosition(Vec2(100, 0));
	//mBack->setAnchorPoint(Vec2(0.5f,0));
	items.pushBack(mBack);

	mReplay = MenuItemLabel::create(Label::createWithTTF("REPLAY", "fonts/Karate.ttf", 37),CC_CALLBACK_1(PhiTieuHUDLayer::ClickReplay, this));
	mReplay->setPosition(Vec2(-100, 0));
	//mReplay->setAnchorPoint(Vec2(0.5f,0));
	items.pushBack(mReplay);

	menu = Menu::createWithArray(items);
	//menu->setAnchorPoint(Vec2(0.5f,0));
	menu->setPosition(Config::screenSize.width/2, 100 - Config::screenSize.height);
	this->addChild(menu);

	over = Sprite::create("PhiTieu/gameover.png");
	over->setPosition(Config::centerPoint + Vec2(0, 800));
	over->setScale(0.5f);
	this->addChild(over);

	score = 0;
	PhiTieuHUDLayer::Instance = this;
	//this->setScale(Config::getScaleSize());
	return true;
}
void PhiTieuHUDLayer::ClickBack(Ref* f) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
}

void PhiTieuHUDLayer::tangHeart() {
	hearts.pushBack(Item::getHeart(hearts.size() + 1));
	this->addChild(hearts.at(hearts.size() - 1));

}

int PhiTieuHUDLayer::getMang() {
	return hearts.size();
}

void PhiTieuHUDLayer::ClickReplay(Ref* f) {
	auto scene = PhiTieuScene::createScene(1);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::RED));
}

void PhiTieuHUDLayer::matMau() {
	if (hearts.size() > 0) {
		hearts.at(hearts.size() - 1)->removeFromParent();
		hearts.popBack();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PhiTieu/Fail.mp3");
	}
	if (hearts.size() == 0)
	{
		gameOver();
		_phiTieuLayer->gameOver();
	}
}

bool PhiTieuHUDLayer::touch_PhongTieu(Touch* t, Event* e) {
	if (Ninja::Instance != nullptr)
		if (power->fire())
			_phiTieuLayer->PhongTieu(t->getLocation());

	return true;
}

void PhiTieuHUDLayer::click_Jump(Ref* sender, TouchEventType touchType) {
	//Thực hiện nhảy
	if (touchType == TouchEventType::TOUCH_EVENT_BEGAN) {
		_phiTieuLayer->Jump();
	}
}

void PhiTieuHUDLayer::gameOver() {
	if(score > highScore)
		UserDefault::getInstance()->setIntegerForKey("score4", score);
	//UserDefault::getInstance()->flush();
	over->runAction(MoveBy::create(0.5f, Vec2(0, -750)));
	menu->runAction(MoveBy::create(0.5f, Vec2(0, Config::screenSize.height)));

	bt_jump->removeFromParent();
	power->removeFromParent();
	for (auto e : hearts)
		e->removeFromParent();

}

void PhiTieuHUDLayer::tangDiem() {
	score++;
	std::stringstream ss;
	ss << score;
	txt_score->setString(ss.str());

	//Animation
	auto phongTo = ScaleTo::create(0.1f, 1.8);
	auto thuNho = ScaleTo::create(0.1f, 1);
	txt_score->runAction(Sequence::createWithTwoActions(phongTo, thuNho));

}
