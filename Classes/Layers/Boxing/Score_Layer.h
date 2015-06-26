#ifndef _Score_Layer_
#define _Score_Layer_
#include "cocos2d.h"
USING_NS_CC;

class Score_Layer : public Layer
{
public:
	Score_Layer();
	~Score_Layer();
	static Score_Layer * create_Score_Layer();
	bool init();
	void update(float delta);

	void headSprite();
	static void updateScore();
	static void updateLive();

	void gameOver();

};

#endif