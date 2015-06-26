#ifndef _Start_Layer_
#define _Start_Layer_
#include "cocos2d.h"
USING_NS_CC;

class Start_Layer : public Layer
{
public:
	Start_Layer();
	~Start_Layer();
	static Start_Layer * create_Start_Layer();
	bool init();
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

};

#endif
