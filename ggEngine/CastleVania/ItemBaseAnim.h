#pragma once
#include <ggEngine.h>
#include "CVSprite.h"
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class CVGame;
class Simon;
class ItemBaseAnim : public CVSpriteAnimation {
public:
	ItemBaseAnim(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~ItemBaseAnim();
	void SetLiveTime(unsigned int liveTime);


	virtual void CheckCollisionToSimon(Simon *simon);
	virtual void OnSimonContact(Simon *simon, ColliderArg e);
	virtual void Destroy();
	virtual void Active();
protected:
	unsigned int liveTime = -1;
	CVGame *cvGame;
	TimeBasedEventInfo * timeEvent = nullptr;
};