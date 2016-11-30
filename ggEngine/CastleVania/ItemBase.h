#pragma once
#include <ggEngine.h>
#include "CVSprite.h"
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class CVGame;
class Simon;
class ItemBase : public CVSprite{
public:
	ItemBase(CVGame *cvGame, SpriteInfo *image);
	~ItemBase();
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