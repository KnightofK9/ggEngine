#pragma once
#include "EnemyBase.h"
class TweenEnemyBase : public EnemyBase {
public:
	TweenEnemyBase(CVGame *cvGame, SpriteInfo *spriteInfo, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~TweenEnemyBase();
protected:
};