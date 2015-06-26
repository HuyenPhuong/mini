#ifndef _Kid_Layer_
#define _Kid_Layer_
#include "cocos2d.h"
USING_NS_CC;

class Kid_Layer : public Layer
{
public:
	Kid_Layer();
	~Kid_Layer();
	static Kid_Layer * create_Kid_Layer();
	bool init();
	
	//Physics
	PhysicsWorld * physicsWorld;
	void SetPhysicsWorld(PhysicsWorld *world);

	static void gameOver();

};

#endif