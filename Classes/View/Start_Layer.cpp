#include "Start_Layer.h"
#include "View/Play_Scene.h"
#include "Utility/Config.h"
#include "ui/CocosGUI.h"
#include "Model/Skater.h"
#include "SimpleAudioEngine.h"
using namespace ui;

Start_Layer::Start_Layer()
{
}

Start_Layer::~Start_Layer()
{
}

bool Start_Layer::init()
{
	if (!Layer::init()) return false;

	//Back button
	this->setKeypadEnabled(true);
	this->setKeyboardEnabled(true);

	//Background
	auto background = Sprite::create("Background/Background_4.jpg");
	background->setPosition(Config::centerPoint);
	background->setScale(Config::getScale(background));
	this->addChild(background, 0);

	//SkaterKid
	Skater * skater = Skater::create("0.png");
	skater->setScale(1.2);
	skater->runAnimation_Run();
	skater->setPosition(Config::centerPoint.x - 250, Config::centerPoint.y - 155);
	this->addChild(skater);

	//Button
	Button * play_Button = Button::create("Button/play.png", "Button/play.png", "Button/play.png");
	play_Button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	play_Button->setPosition(Config::centerPoint);
	play_Button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/start.mp3");
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, Play_Scene::create_Play_Scene(), Color3B::WHITE));
			break;
		default:
			break;
		}
	});
	this->addChild(play_Button, 1);

	return true;
}

Start_Layer * Start_Layer::create_Start_Layer()
{
	Start_Layer * layer = new Start_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}

void Start_Layer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
	}
}
