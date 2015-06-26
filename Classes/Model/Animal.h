#ifndef _Animal_
#define _Animal_

#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Animal : public Node
{
private:
	Sprite* _sprite;
	bool init(string fileName);
	PhysicsBody *body;
public:
	Animal();
	~Animal();
	static Animal * create(string fileName);
	void runAnimation(string name, int count, float time, bool isRepeat);
	void MoveAnimal(float speed);
};

#endif
