#ifndef _Start_Scene_
#define _Start_Scene_
#include "cocos2d.h"
USING_NS_CC;

class Start_Scene : public Scene
{
public:
	Start_Scene();
	~Start_Scene();
	static Scene * create_Start_Scene();
	bool init();

};

#endif