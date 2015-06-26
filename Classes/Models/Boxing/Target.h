#ifndef _Target_
#define _Target_

#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Target : public Node
{
private:
	Sprite* _sprite;
	bool init(string fileName);
	PhysicsBody *body;
public:
	Target();
	~Target();
	static Target* create(string fileName);
	void runAnimation(string name, int count, float time, bool isRepeat);
};
#endif