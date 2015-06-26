/*
 * Battery.h
 *
 *  Created on: Jun 24, 2015
 *      Author: Dang
 */

#ifndef MODEL_BATTERY_H_
#define MODEL_BATTERY_H_
#include "cocos2d.h"
USING_NS_CC;

class Battery : public Node
{
public:
	Battery();
	virtual ~Battery();
	Sprite * sprite;
	PhysicsBody * body;
	bool init();
	static Battery * create_Battery();
	void MoveBattery(float speed);
};

#endif /* MODEL_BATTERY_H_ */
