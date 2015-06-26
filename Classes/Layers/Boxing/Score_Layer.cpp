#include "Score_Layer.h"
#include "Utility/Config.h"
#include <iostream>
#include "ui/CocosGUI.h"
#include "Scenes/Boxing/Play_Scene.h"
#include "Scenes/Boxing/Start_Scene.h"
#include "Control/Boxing/Controller.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;
using namespace ui;
int lifecount;
int _score1;
int _highscore;
Label* _label;
Label* _scoreText;
Label* _labelhighscore;
Label* _highscoreText;
bool isAlive=true;

Score_Layer::Score_Layer()
{
}


Score_Layer::~Score_Layer()
{
}



bool Score_Layer::init()
{
	lifecount = 3;
	_score1 = 0;
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (!Layer::init()) return false;

	//score
	

	_label = Label::create("Score:   ", "Arial", 20);
	_label->setColor(ccc3(192, 57, 43));
	_label->setPosition(winSize.width - 120, winSize.height - 20);
	this->addChild(_label);

	_scoreText = Label::create();
	_scoreText->setColor(ccc3(192, 57, 43));
	_scoreText->setPosition(winSize.width - 50, winSize.height - 20);
	_scoreText->setString("0");
	_scoreText->setSystemFontSize(25);
	this->addChild(_scoreText);

	_labelhighscore = Label::create("High Score:   ", "Arial", 20);
	_labelhighscore->setColor(ccc3(192, 57, 43));
	_labelhighscore->setPosition(winSize.width - 120, winSize.height - 50);
	this->addChild(_labelhighscore);

	_highscoreText = Label::create();
	_highscoreText->setColor(ccc3(192, 57, 43));
	_highscoreText->setPosition(winSize.width - 50, winSize.height - 50);

	//lấy ra high score
	_highscoreText->setSystemFontSize(25);
	_highscore = UserDefault::getInstance()->getIntegerForKey("score2");
	stringstream ss;
	ss << _highscore;
	_highscoreText->setString(ss.str());
	this->addChild(_highscoreText);

	//mạng
	headSprite();

	this->scheduleUpdate();

	return true;
}

Score_Layer * Score_Layer::create_Score_Layer()
{
	Score_Layer * layer = new Score_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}

void Score_Layer::headSprite()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	auto head1 = Sprite::create("Boxing/heart.png");
	head1->setPosition(Vec2(50, winSize.height - 50));
	head1->setScale(0.3);
	this->addChild(head1, 0);
	head1->setTag(16);
	auto head2 = Sprite::create("Boxing/heart.png");
	head2->setPosition(Vec2(110, winSize.height - 50));
	head2->setScale(0.3);
	this->addChild(head2, 0);
	head2->setTag(17);
	auto head3 = Sprite::create("Boxing/heart.png");
	head3->setPosition(Vec2(170, winSize.height - 50));
	head3->setScale(0.3);
	this->addChild(head3, 0);
	head3->setTag(18);
}

void Score_Layer::updateScore()
{
	if (isAlive==true)
	{
	_score1 += 10;
	stringstream ss;
	ss << _score1;
	_scoreText->setString(ss.str());
	}

}

void Score_Layer::updateLive()
{
	lifecount--;
}


void Score_Layer::update(float delta)
{
	if (lifecount >= 3)
	{

	}
	if (lifecount == 2)
	{
		this->removeChildByTag(18);
		CCLOG("Con 2 mang");
	}
	if (lifecount == 1)
	{
		this->removeChildByTag(17);
		CCLOG("Con 1 mang");
	}
	if (lifecount < 1)
	{
		this->removeChildByTag(16);
		CCLOG("Game over");
		
		gameOver();

		//luu highscore
		if (_score1>_highscore)
			UserDefault::getInstance()->setIntegerForKey("score2", _score1);
	}
}

void Score_Layer::gameOver()
{
	isAlive = false;

	Controller_Layer::gameOver();
	
	//Nền mờ
	Sprite * opacity = Sprite::create("Boxing/opacity.png");
	opacity->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	opacity->setOpacity(20);

	opacity->setPosition(Config::centerPoint);
	this->addChild(opacity, 20);

	//remove sự kiện ontouch
	//Director::getInstance()->getEventDispatcher()->setEnabled(false);

	//Replay Button
	Button * replayButton = Button::create("Boxing/replay_button.png");
	replayButton->setScale(1.2);
	replayButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	replayButton->setPosition(Config::centerPoint);
	replayButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//tạo music
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Boxing/beep1.mp3");

			Director::getInstance()->replaceScene(TransitionFade::create(0.5, Play_Scene::create_Play_Scene(), Color3B::WHITE));
			isAlive = true;
			break;
		default:
			break;
		}
	});
	this->addChild(replayButton,21);

	
	
}