#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"

using namespace ggEngine;
class CVGame;
class WeaponWhip;
class WeaponBase;

class BreakableObjectBase : public CVSpriteAnimation
{
public:
	BreakableObjectBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~BreakableObjectBase();

	virtual void CheckCollisionToWeaponWhip(WeaponWhip *whip);
	virtual void OnWeaponWhipContact(WeaponWhip *whip, ColliderArg e);

	virtual void CheckCollisionToSubWeapon(WeaponBase *weapon);
	virtual void OnSubWeaponContact(WeaponBase *weapon, ColliderArg e);

	virtual void Active();
};

