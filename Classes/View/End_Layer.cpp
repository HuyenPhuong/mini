#include "End_Layer.h"
#include "Utility/Config.h"
#include "ui/CocosGUI.h"
#include "View/Play_Scene.h"
#include "SimpleAudioEngine.h"
#include <sstream>
using namespace std;
using namespace ui;

End_Layer::End_Layer()
{
}


End_Layer::~End_Layer()
{
}

bool End_Layer::init(int score)
{
	if (!Layer::init()) return false;

	//Background
	auto background = Sprite::create("BackgroundEnd.jpg");
	background->setPosition(Config::centerPoint);
	background->setScale(Config::getScale(background));
	this->addChild(background, 0);

	//Replay Button
	Button * replay_Button = Button::create("Button/ReplayButton.png", "Button/ReplayButton.png", "Button/ReplayButton.png");
	replay_Button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	replay_Button->setPosition(Config::centerPoint);
	replay_Button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
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
	this->addChild(replay_Button, 1);

	//Text current Score
	Label * text_current_Score = Label::create("Score:", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	text_current_Score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	text_current_Score->setColor(Color3B::WHITE);
	text_current_Score->setPosition(0, Config::screenSize.height);
	this->addChild(text_current_Score);

	//Current Score
	stringstream ss;
	ss << score;
	Label * current_Score = Label::create(ss.str(), "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	current_Score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	current_Score->setColor(Color3B::WHITE);
	current_Score->setPosition(text_current_Score->getContentSize().width * 3 / 2, Config::screenSize.height);
	this->addChild(current_Score);

	return true;
}

End_Layer * End_Layer::create_End_Layer(int score)
{
	End_Layer * layer = new End_Layer();
	layer->init(score);
	layer->autorelease();
	return layer;
}