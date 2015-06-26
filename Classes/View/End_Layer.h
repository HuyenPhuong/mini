#ifndef _End_Layer_
#define _End_Layer_
#include "cocos2d.h"
USING_NS_CC;

class End_Layer : public Layer
{
public:
	End_Layer();
	~End_Layer();
	static End_Layer * create_End_Layer(int score);
	bool init(int score);
};

#endif