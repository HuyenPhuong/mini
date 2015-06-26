#ifndef _End_Scene_
#define _End_Scene_
#include "cocos2d.h"
USING_NS_CC;

class End_Scene : public Scene
{
public:
	End_Scene();
	~End_Scene();
	static Scene * create_End_Scene(int score);
	bool init();
};

#endif