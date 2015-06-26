#ifndef _CAR_
#define _CAR_
#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Car : public Node
{
private:
	Sprite* _sprite;
	bool init(string fileName);
	PhysicsBody *body;
public:
	Car();
	~Car();
	static Car* create(string fileName);
	float speed_Obs;
	void MoveCar(float speed, float distance);
	void MoveCar(float speed);
	void runAnimation(string name, int count, float time, bool isRepeat);
};




#endif
