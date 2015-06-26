#include "Start_Layer.h"
#include "Models/Boxing/Kid.h"
#include "Scenes/Boxing/Play_Scene.h"
#include "Utility/Config.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace ui;

Kid* kid11;
Kid* kid22;
Kid *kid33;
Kid *kid44;
Kid *kid55;

Start_Layer::Start_Layer()
{
}

Start_Layer::~Start_Layer()
{
}

bool Start_Layer::init()
{

	if (!Layer::init()) return false;

	//kid sprite
	kid11 = Kid::create("Boxing/face11.png");
	kid11->moveAction();
	this->addChild(kid11, 1);


	kid22 = Kid::create("Boxing/face21.png");
	kid22->moveAction();
	this->addChild(kid22, 1);


	kid33 = Kid::create("Boxing/face31.png");
	kid33->moveAction();
	this->addChild(kid33, 1);

	kid44 = Kid::create("Boxing/face41.png");
	kid44->moveAction();
	this->addChild(kid44, 1);

	kid55 = Kid::create("Boxing/face51.png");
	kid55->moveAction();
	this->addChild(kid55, 1);



	Button * play_Button = Button::create("Boxing/Start2.png", "Boxing/Start1.png", "Boxing/Start2.png");
	play_Button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	play_Button->setPosition(Point(Config::centerPoint.x, Config::centerPoint.y - 190));
	play_Button->setScale(0.4);
	play_Button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//tạo music
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Boxing/beep1.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Boxing/beep1.mp3");

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