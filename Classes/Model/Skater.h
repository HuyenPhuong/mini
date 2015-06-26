#ifndef _Skater_
#define _Skater_

#include "cocos2d.h"
#include <sstream>
#include <iostream>

USING_NS_CC;
using namespace std;

class Skater : public Node
{
public:
	Sprite * _sprite;
	bool init(string fileName);
	PhysicsBody * body;
	
public:
	Skater();
	~Skater();
	bool isDeath;
	bool isJumping;
	bool isDoubleJump;
	bool isSitting;
	bool isIncrease;
	bool bonusX2;
	bool magnet;
	int coin;
	int score;
	float battery;
	static Skater* create(string fileName);

	void runAnimation(string name, int count, float time, bool isRepeat);
	void runAnimation_Reserve(string name, int count, float time, bool isRepeat);
	void runAnimation_Run();
	void runAnimation_Jump();
	void runAnimation_Fail();
	void runAnimation_Up();
	void runAnimation_Between_Up_And_Down();
	void runAnimation_Down();

	void jump_Action();
	void jump_Action_Double();
	bool onContactBegin(PhysicsContact &contact);
};




#endif
