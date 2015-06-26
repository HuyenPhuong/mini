#include "Play_Scene.h"
#include "View/Object_Layer.h"
#include "View/Background_Layer.h"
#include "Utility/Config.h"
#include "Control/GamePlay.h"
#include "View/Score_Layer.h"

Play_Scene::Play_Scene()
{
}

Play_Scene::~Play_Scene()
{
}

bool Play_Scene::init()
{
	if (!Play_Scene::init()) return false;

	return true;
}

Scene * Play_Scene::create_Play_Scene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setSpeed(3.0f);
	scene->getPhysicsWorld()->setGravity(Vect(0, -145.0f));
	scene->getPhysicsWorld()->setUpdateRate(0.5f);
	scene->getPhysicsWorld()->setSubsteps(10);

	//Background layer
	auto bgLayer = Background_Layer::create_Background_Layer();
	scene->addChild(bgLayer);

	//Show Kid and Object
	auto object_Layer = Object_Layer::create_Object_Layer();
	object_Layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(object_Layer);

	//Score
	auto score_layer = Score_Layer::create_Score_Layer();
	scene->addChild(score_layer);

	//Gameplay
	auto gamePlay = GamePlay::createGamePlayLayer();
	gamePlay->Set_Object_Layer(object_Layer);
	gamePlay->Set_Background_Layer(bgLayer);
	gamePlay->Set_Score_Layer(score_layer);
	scene->addChild(gamePlay);

	return scene;
}
