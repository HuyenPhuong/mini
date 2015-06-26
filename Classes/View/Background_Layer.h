#ifndef _Start_Layer_
#define _Start_Layer_
#include "cocos2d.h"
USING_NS_CC;

class Background_Layer : public Layer
{
public:
	Background_Layer();
	~Background_Layer();
	static Background_Layer * create_Background_Layer();
	bool init();
	void endlessBackground();
	float speed_Scroll;
	void update(float dt);
	Sprite* _oddBackground;
	Sprite* _evenBackground;
};

#endif
