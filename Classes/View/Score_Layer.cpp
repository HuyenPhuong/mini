#include "Score_Layer.h"
#include "Utility/Config.h"
#include "Model/PowerSpeed.h"
#include <sstream>
using namespace std;


Score_Layer::Score_Layer()
{
	this->heso_Scale = 1.0f;
}


Score_Layer::~Score_Layer()
{
}

bool Score_Layer::init()
{
	if (!Layer::init()) return false;
	
	//Text current Score
	Label * text_current_Score = Label::create("Score:", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	text_current_Score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	text_current_Score->setColor(Color3B::WHITE);
	text_current_Score->setPosition(0, Config::screenSize.height);
	this->addChild(text_current_Score);

	//Text best Score
	Label * text_best_Score = Label::create("Highscore:", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	text_best_Score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	text_best_Score->setColor(Color3B::WHITE);
	text_best_Score->setPosition(0, Config::screenSize.height - text_current_Score->getContentSize().height * 3 / 2.5);
	this->addChild(text_best_Score);

	//Current Score
	current_Score = Label::create("0", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	current_Score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	current_Score->setColor(Color3B::WHITE);
	current_Score->setPosition(text_best_Score->getContentSize().width * 3 / 2, Config::screenSize.height);
	this->addChild(current_Score);

	//best Score
	stringstream ss;
	ss << UserDefault::getInstance()->getIntegerForKey("BESTSCORE");
	best_Score = Label::create(ss.str(), "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	best_Score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	best_Score->setColor(Color3B::WHITE);
	best_Score->setPosition(text_best_Score->getContentSize().width * 3 / 2, Config::screenSize.height - text_current_Score->getContentSize().height * 3 / 2.5);
	this->addChild(best_Score);

	//Sprite Coin
	Sprite * sprite_Coin = Sprite::create("Coin/coin4.png");
	sprite_Coin->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	//sprite_Coin->setScale(0.2);
	sprite_Coin->setPosition(Config::screenSize.width * 8.25 / 10, Config::screenSize.height);
	this->addChild(sprite_Coin);

	//Text Coin
	Label * text_Coin = Label::create("x", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	text_Coin->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	text_Coin->setColor(Color3B::WHITE);
	text_Coin->setPosition(Config::screenSize.width * 8.5 / 10 + text_Coin->getContentSize().width / 2, Config::screenSize.height);
	this->addChild(text_Coin);

	//Coin
	coin = Label::create("0", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	coin->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coin->setColor(Color3B::WHITE);
	coin->setPosition(Config::screenSize.width * 8.75 / 10 + text_Coin->getContentSize().width / 2, Config::screenSize.height);
	this->addChild(coin);

	//Power Speed
	Label * power_Label = Label::create("Power:", "fonts/Kidfont.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	power_Label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	power_Label->setColor(Color3B::WHITE);
	power_Label->setPosition(Config::screenSize.width / 2 , Config::screenSize.height - text_current_Score->getContentSize().height * 3 / 2.5);
	this->addChild(power_Label);

	Sprite * border = Sprite::create("Power_Speed_Border.png");
	border->setPosition(Config::screenSize.width / 2 + power_Label->getContentSize().width + 10, power_Label->getPositionY() - power_Label->getContentSize().height/2);
	border->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->addChild(border);

	this->power_bar = Power_Speed::create_Power_Speed();
	this->power_bar->setPosition(Config::screenSize.width / 2 + power_Label->getContentSize().width + 10, power_Label->getPositionY() - power_Label->getContentSize().height/2);
	this->power_bar->Set_Scale(this->heso_Scale);
	this->addChild(power_bar);
	return true;
}

Score_Layer * Score_Layer::create_Score_Layer()
{
	Score_Layer * layer = new Score_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}

void Score_Layer::UpdatePower()
{
	this->power_bar->Set_Scale(this->heso_Scale);
}
