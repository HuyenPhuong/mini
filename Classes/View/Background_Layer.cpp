#include "Background_Layer.h"
#include "Utility/Config.h"

Background_Layer::Background_Layer()
{
	speed_Scroll = 150;
}


Background_Layer::~Background_Layer()
{
}

bool Background_Layer::init()
{
	if (!Layer::init()) return false;

	endlessBackground();
	return true;
}

Background_Layer * Background_Layer::create_Background_Layer()
{
	Background_Layer * layer = new Background_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}

void Background_Layer::endlessBackground() {
	// Create the two background sprites which will alternate
	_oddBackground = Sprite::create("Background/Background_3.png");
	_evenBackground = Sprite::create("Background/Background_3.png");
	_oddBackground->setScale(Config::getScale(_oddBackground));
	_evenBackground->setScale(Config::getScale(_evenBackground));
	// One starts dead centre and one starts exactly one screen height above
	_oddBackground->setPosition(Config::centerPoint);
	_evenBackground->setPosition(Config::screenSize.width * 3 / 2, Config::screenSize.height / 2);

	this->addChild(_oddBackground);
	this->addChild(_evenBackground);
	// Schedule the scrolling action
	this->scheduleUpdate();
	// Add sprites to the layer
	
}

void Background_Layer::update(float dt) {

	_oddBackground->setPosition(_oddBackground->getPosition().x - speed_Scroll * dt, _oddBackground->getPosition().y);
	_evenBackground->setPosition(_evenBackground->getPosition().x - speed_Scroll * dt, _evenBackground->getPosition().y);

	// reset position when they are off from view.
	if (_oddBackground->getPosition().x < -Config::screenSize.width / 2)
	{
		_oddBackground->setPosition(Config::screenSize.width / 2, Config::screenSize.height / 2);
		_evenBackground->setPosition(Config::screenSize.width / 2 + Config::screenSize.width, Config::screenSize.height / 2);
	}
}
