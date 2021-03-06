﻿#include "Scenes/HelloWorldScene.h"
#include "Layers/BanSung/BanTao_Layer.h"
#include "Scenes/BanSung/BanTao_Scence.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "Models/BanSung/BanTao_Target.h"
#include "Models/BanSung/BanTao_Apple.h"
#include "Utility/Config.h"
#include "Utility/XHelper.h"
#include "SimpleAudioEngine.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace ui;

BanTao_Layer::BanTao_Layer() { }
BanTao_Layer::~BanTao_Layer(){ }


int mang;
float speed;
int score1;
int highscore;
Label* label;
Label* scoreText;
Label* labelhighscore;
Label* highscoreText;
Vec2 tamAple;
BanTao_Apple* apple;

bool BanTao_Layer::init()
{
	mang = 3;
	speed = 1;
	score1 = 0;

	if (!Layer::init())
		return false;

	this->setKeypadEnabled(true);
	this->setKeyboardEnabled(true);

	//Hiển thị background
	Sprite* background = Sprite::create("BanSung/soc_bg.jpg");
	background->setPosition(Config::centerPoint);
	background->setScale(Config::getScale(background));
	this->addChild(background, -1);
	
	//music
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BanSung/music.mp3", true);

	//score
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	label = Label::create("Score:   ", "Arial", 20);
	label->setColor(ccc3(192, 57, 43));
	label->setPosition(winSize.width - 120, winSize.height - 20);
	this->addChild(label);

	scoreText = Label::create();
	scoreText->setColor(ccc3(192, 57, 43));
	scoreText->setPosition(winSize.width - 50, winSize.height - 20);
	scoreText->setString("0");
	scoreText->setSystemFontSize(25);
	this->addChild(scoreText);
	
	labelhighscore = Label::create("High Score:   ", "Arial", 20);
	labelhighscore->setColor(ccc3(192, 57, 43));
	labelhighscore->setPosition(winSize.width - 120, winSize.height - 50);
	this->addChild(labelhighscore);

	highscoreText = Label::create();
	highscoreText->setColor(ccc3(192, 57, 43));
	highscoreText->setPosition(winSize.width - 50, winSize.height - 50);

	//lấy ra high score
	highscoreText->setSystemFontSize(25);
	highscore = UserDefault::getInstance()->getIntegerForKey("score1");
	stringstream ss;
	ss << highscore;
	highscoreText->setString(ss.str());
	this->addChild(highscoreText);

	//Thêm mạng
	headSprite();
	
	//Thêm Animation kid 
	auto kidstart = Sprite::create("BanSung/kid.png");
	kidstart->setPosition(Config::centerPoint.x, Config::centerPoint.y);
	kidstart->setScale(1.2);
	XHelper::runAnimation("kidstart", 2, 0.5f, true, kidstart);
	this->addChild(kidstart);
	kidstart->setTag(15);

	//Thêm comment
	commentPut("BanSung/commentStart.png");


	//button start
	auto button = Button::create("BanSung/Start2.png", "BanSung/Start1.png", "BanSung/Start2.png");
	button->setTag(12);
	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			std::cout << "Button 1 clicked" << std::endl;
			onStart(speed);
			break;
		default:
			break;
		}
	});
	button->setPosition(Point(Config::centerPoint.x, Config::centerPoint.y - 190));


	button->setScale(0.4);
	this->addChild(button);

	//button back
	auto backButton = Button::create("BanSung/backbutton.png", "BanSung/backbutton2.png");
	backButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
												  auto scene = HelloWorld::createScene();
												  Director::getInstance()->replaceScene(scene);
												  CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
												  
		}
			break;
		default:
			break;
		}
	});
	backButton->setPosition(Vec2(100, 100));
	this->addChild(backButton, 0);

	return true;
}

void BanTao_Layer::onStart( float speed)
{
	//xóa buttonStart, comment
	this->removeChildByTag(12);
	this->removeChildByTag(10);

	//Thêm target
	BanTao_Target* target = BanTao_Target::create("BanSung/target2.png",speed);
	target->moveAction(speed);
	this->addChild(target, 1);
	
	//Thêm apple
	appleSprite();
	
	//Touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BanTao_Layer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BanTao_Layer::onTouchEnded, this, target);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}



bool BanTao_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}


void BanTao_Layer::onTouchEnded(Touch *touch, Event *unused_event, BanTao_Target *target)
{
	//tạo paticle
	auto emitter = ParticleFire::create();
	Vec2 xxx = touch->getLocation();
	emitter->setPosition(target->getPosition());
	emitter->setDuration(0.5);
	this->addChild(emitter, 10);
	emitter->setTag(14);

	//tạo music
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BanSung/shot.wav");

	//tính xem tọa độ của cái target có trùng quả táo không?
	// nếu trùng thì quả táo biến mất
	if (XHelper::checkShoot(tamAple, 30, target->getPosition()))
	{

		commentPut("BanSung/commentWin.png");
		//xóa đi apple
		this->removeChildByTag(11);
		
		//thêm lại apple 
		this->runAction(Sequence::create(
			DelayTime::create(1),
			CallFunc::create(CC_CALLBACK_0(BanTao_Layer::appleSprite, this)),
			nullptr));

		//set lại speed cho target
		speed = speed - 0.08;
		target->stopAllActions();
		target->moveAction(speed);

		//set lại scale cho target nếu điểm >50
		if (score1>40)
		{
		target->setScaleTarget(0.08);
		}
		
		if (score1 > 80)
		{
		target->setScaleTarget(0.06);
		speed = speed + 0.04;
		}
		

		//cập nhật score
		CCLOG("Score: %f", score1);
		updateScore();
		

		
	}
	else
	{

		mang--;
		CCLOG("Mang: %d", mang);
		commentPut("BanSung/commentFail.png");
		checkLive();
	}
	
}


void BanTao_Layer::commentPut(string name)
{

	auto comment = Sprite::create(name);
	comment->setPosition(Point(Config::centerPoint.x + 150, Config::centerPoint.y + 150));
	comment->setScale(0.8);
	this->addChild(comment);
	comment->setTag(10);
}

void BanTao_Layer::appleSprite()
{
	 apple = BanTao_Apple::create("BanSung/apple.png");
	int i = cocos2d::random(1, 3);
	Vec2 v1 = Vec2(Config::centerPoint.x, Config::centerPoint.y + 158);
	Vec2 v2 = Vec2(Config::centerPoint.x-60, Config::centerPoint.y + 158-15);
	Vec2 v3 = Vec2(Config::centerPoint.x+60, Config::centerPoint.y + 158-15);
	switch (i)
	{
	case 1: apple->setPotionApple(v1); tamAple = v1;; break;
	case 2: apple->setPotionApple(v2); apple->setRotation(-25); tamAple = v2; break;
	case 3: apple->setPotionApple(v3); apple->setRotation(25); tamAple = v3; break;
	}
	apple->setScale(0.5);
	this->addChild(apple);
	apple->setTag(11);

}

void BanTao_Layer::headSprite()
{
	auto head1 = Sprite::create("BanSung/head1.png");
	head1->setPosition(Vec2(Config::centerPoint.x - 350, Config::centerPoint.y + 200));
	head1->setScale(0.6);
	this->addChild(head1, 0);
	head1->setTag(16);
	auto head2 = Sprite::create("BanSung/head1.png");
	head2->setPosition(Vec2(Config::centerPoint.x - 290, Config::centerPoint.y + 200));
	head2->setScale(0.6);
	this->addChild(head2, 0);
	head2->setTag(17);
	auto head3 = Sprite::create("BanSung/head1.png");
	head3->setPosition(Vec2(Config::centerPoint.x - 230, Config::centerPoint.y + 200));
	head3->setScale(0.6);
	this->addChild(head3, 0);
	head3->setTag(18);
}
void BanTao_Layer::checkLive()
{
	

	if (mang>=3)
	{
		
	}
	if (mang==2)
	{
		this->removeChildByTag(18);
		CCLOG("Con 2 mang");
	}
	if (mang==1)
	{
		this->removeChildByTag(17);
		CCLOG("Con 1 mang");
	}
	if (mang<1)
	{
		this->removeChildByTag(16);
		CCLOG("Game over");
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);

		//xóa đi cái target, thằng người để cho thằng khác vào!
		this->removeChildByTag(10);
		this->removeChildByTag(13);
		this->removeChildByTag(15);


		commentPut("BanSung/commentGameOver.png");

		auto kidcry = Sprite::create("BanSung/kid.png");
		kidcry->setPosition(Config::centerPoint.x, Config::centerPoint.y);
		kidcry->setScale(1.2);
		XHelper::runAnimation("cry", 2, 0.5f, true, kidcry);
		this->addChild(kidcry);
		kidcry->setTag(15);
		//luu highscore
		if (score1>highscore)
			UserDefault::getInstance()->setIntegerForKey("score1", score1);

		this->runAction(Sequence::create(
			DelayTime::create(2),
			CallFunc::create(CC_CALLBACK_0(BanTao_Layer::restart, this)),
			nullptr));


	}
}

void BanTao_Layer::restart()
{
	
	auto newScene = BanTao_Scence::create();
	Director::getInstance()->replaceScene(newScene);
}


void BanTao_Layer::updateScore()
{		
	
		score1 += 10; 
		stringstream ss;
		ss << score1;
		scoreText->setString(ss.str());
	
}

void BanTao_Layer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		auto scene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
	}
}