#include "End_Scene.h"
#include "View/End_Layer.h"


End_Scene::End_Scene()
{
}


End_Scene::~End_Scene()
{
}

bool End_Scene::init()
{
	if (!Scene::init()) return false;




	return true;
}

Scene* End_Scene::create_End_Scene(int score)
{
	auto scene = Scene::create();

	//End Layer
	auto endLayer = End_Layer::create_End_Layer(score);
	scene->addChild(endLayer);

	return scene;
}