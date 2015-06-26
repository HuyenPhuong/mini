#include "Start_Scene.h"
#include "Utility/Config.h"
#include "View/Start_Layer.h"
#include "View/Background_Layer.h"

Start_Scene::Start_Scene()
{
}

Start_Scene::~Start_Scene()
{
}

bool Start_Scene::init()
{
	if (!Scene::init()) return false;
	return true;
}

Scene* Start_Scene::create_Start_Scene()
{
	auto scene = Scene::create();

	//Screen Config
	Config::screenSize = Director::getInstance()->getVisibleSize();
	Size screenSize = Config::screenSize;
	Vec2 center(screenSize.width / 2, screenSize.height / 2);
	Config::centerPoint = center;

	
	//Start Layer
	auto startLayer = Start_Layer::create_Start_Layer();
	scene->addChild(startLayer);

	//Background layer
	

	return scene;
}