#include "CVSpriteAnimation.h"
#include "CVGame.h"
CVSpriteAnimation::CVSpriteAnimation(CVGame *cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) :SpriteAnimation(cvGame->GetDrawManager(), image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->cvGame = cvGame;
}

CVSpriteAnimation::~CVSpriteAnimation()
{
}
