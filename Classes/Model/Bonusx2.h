#ifndef _Bonusx2_
#define _Bonusx2_

#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Bonusx2 : public Node
{
private:
	Sprite* _sprite;
	bool init(string fileName);
	PhysicsBody *body;
public:
	Bonusx2();
	~Bonusx2();
	static Bonusx2* create(string fileName);
	void runAnimation(string name, int count, float time, bool isRepeat);
};




#endif