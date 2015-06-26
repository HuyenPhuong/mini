/*
 * Bird.h
 *
 *  Created on: Jun 22, 2015
 *      Author: Dang
 */

#ifndef MODEL_BIRD_H_
#define MODEL_BIRD_H_
#include "cocos2d.h"
#include <sstream>
#include <iostream>
USING_NS_CC;
using namespace std;

class Bird : public Node
{
	private:
	Sprite* _sprite;
	bool init(string fileName);
	PhysicsBody *body;
public:
	Bird();
	virtual ~Bird();
	static Bird * create(string fileName);
	void runAnimation(string name, int count, float time, bool isRepeat);
	void MoveBird(float speed);
};

#endif /* MODEL_BIRD_H_ */
