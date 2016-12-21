#include "TweenEnemyBase.h"

TweenEnemyBase::TweenEnemyBase(CVGame * cvGame, SpriteInfo * spriteInfo, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) : EnemyBase(cvGame, spriteInfo, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->body->immoveable = true;
}

TweenEnemyBase::~TweenEnemyBase()
{
}
