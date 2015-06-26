#ifndef _Kid_
#define _Kid_

#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Kid : public Node
{
private:
	Sprite* _sprite;
	bool init(string fileName);
	bool isAlive;
	PhysicsBody *body;
public:
	Kid();
	~Kid();
	static Kid* create(string fileName);
	Vec2 randomPotision();
	void moveAction();
	void runAnimation(string name, int count, float time, bool isRepeat);
	/*bool onContactBegin(PhysicsContact &contact);*/
};
#endif