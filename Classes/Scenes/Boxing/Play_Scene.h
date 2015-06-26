#ifndef _Play_Scene_
#define _Play_Scene_
#include "cocos2d.h"
#include "Models\Boxing\Kid.h"
USING_NS_CC;

class Play_Scene : public Scene
{

public:
	Play_Scene();
	~Play_Scene();
	static Scene * create_Play_Scene();
	bool init();


	
};

#endif