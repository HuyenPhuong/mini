#include "Background_Layer.h"
#include "Utility/Config.h"

Background_Layer::Background_Layer()
{
}


Background_Layer::~Background_Layer()
{
}

bool Background_Layer::init()
{
	if (!Layer::init()) return false;

	Sprite* background = Sprite::create("Boxing/background.jpg");
	background->setPosition(Config::centerPoint);
	background->setScale(Config::getScale(background));
	this->addChild(background, -1);

	return true;
}

Background_Layer * Background_Layer::create_Background_Layer()
{
	Background_Layer * layer = new Background_Layer();
	layer->init();
	layer->autorelease();
	return layer;
}