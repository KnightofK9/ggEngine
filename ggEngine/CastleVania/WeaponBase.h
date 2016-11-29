#pragma once
#include <ggEngine.h>
#include "CVObject.h"
#include "CVSpriteAnimation.h"
#include "CVGame.h"

class WeaponBase : public CVSpriteAnimation, CVObject
{
public:
	WeaponBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~WeaponBase();
	
	virtual void Active();
	virtual void Destroy();
};

