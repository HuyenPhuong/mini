/*
 * SpawnObs.h
 *
 *  Created on: Jun 17, 2015
 *      Author: Dang
 */

#ifndef MODEL_SPAWNOBS_H_
#define MODEL_SPAWNOBS_H_
#include "cocos2d.h"
USING_NS_CC;

class SpawnObs : public Node
{
public:
	SpawnObs();
	virtual ~SpawnObs();
	static SpawnObs * createSpawnObs();

	//Speed
	float speed_Car;
	float speed_Animal;
	float speed_Bird;
	float speed_Car_2;
	float speed_Animal_2;
	float speed_Bird_2;
	float speed_Battery;

	bool isGenerate;
	void Random_Spawn();
	void SpeedUp_Spawn();
	void SinhCar(float speed);
	void SinhAni(float speed);
	void SinhObs();
	void SinhBird(float speed);
	void SinhBattery();

	//Random
	int max_Random;
};

#endif /* MODEL_SPAWNOBS_H_ */
