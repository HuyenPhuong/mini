/*
 * PowerSpeed.h
 *
 *  Created on: Jun 23, 2015
 *      Author: Dang
 */

#ifndef MODEL_POWERSPEED_H_
#define MODEL_POWERSPEED_H_
#include "cocos2d.h"
USING_NS_CC;

class Power_Speed : public Node
{
public:
	Power_Speed();
	virtual ~Power_Speed();
	bool init();
	Sprite * sprite;
	static Power_Speed * create_Power_Speed();
	void Set_Scale(float scale);
};

#endif /* MODEL_POWERSPEED_H_ */
