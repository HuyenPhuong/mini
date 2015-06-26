#include"Controller.h"
#include "Layers/Boxing/Score_Layer.h"
#include "Layers/Boxing/Kid2_Layer.h"
#include "SimpleAudioEngine.h"

Controller_Layer::Controller_Layer()
{
}


Controller_Layer::~Controller_Layer()
{
}



void Controller_Layer::trungRoi()
{
	CCLOG("Trúng rồi");
	Score_Layer::updateScore();

	//tạo music
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Boxing/beep9.mp3");
}
void Controller_Layer::truotRoi()
{
	CCLOG("Trựơt rồi");
	Score_Layer::updateLive();
	
	//tạo music
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Boxing/beep11.mp3");
}

void Controller_Layer::gameOver()
{
	CCLOG("Gameover rồi");
	Kid_Layer::gameOver();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}