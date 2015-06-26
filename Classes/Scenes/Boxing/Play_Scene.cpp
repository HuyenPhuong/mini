#include "Play_Scene.h"
#include "Layers/Boxing/Kid2_Layer.h"
#include "Layers/Boxing/Background_Layer.h"
#include "Layers/Boxing/Score_Layer.h"
#include "Utility/Config.h"


Play_Scene::Play_Scene()
{
}

Play_Scene::~Play_Scene()
{
}

bool Play_Scene::init()
{
	if (!Play_Scene::init()) return false;

}

Scene * Play_Scene::create_Play_Scene()
{
	auto scene = Scene::createWithPhysics();

	// Lệnh debug này cho phép nhìn thấy các khung body vật lý áp dụng vào các đối tượng ( đường viền đỏ bao quanh đối tượng)
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//Thiết lập gia tốc trọng lực bằng 0, để các đối tượng của chúng ta ko rơi xuống đáy màn hình
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));

	//background Layer
	auto bgLayer = Background_Layer::create_Background_Layer();
	scene->addChild(bgLayer,1);

	//Show Kid and Object
	auto kidLayer = Kid_Layer::create_Kid_Layer();
	scene->addChild(kidLayer, 2);

	//Score
	auto scoreLayer = Score_Layer::create_Score_Layer();
	scene->addChild(scoreLayer, 3);

	return scene;
}
