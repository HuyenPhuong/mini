#ifndef _Coin_
#define _Coin_

#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Coin : public Node
{
private:
	Sprite* _sprite;
	bool init(string fileName);
	PhysicsBody *body;
public:
	Coin();
	~Coin();
	static Coin* create(string fileName);
	void runAnimation(string name, int count, float time, bool isRepeat);
};




#endif