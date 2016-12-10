#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"

using namespace ggEngine;
class CVGame;
class WeaponWhip;
class WeaponBase;
class Candle : public CVSpriteAnimation
{
public:
	Candle(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~Candle();

	void CheckCollisionToWeaponWhip(WeaponWhip *whip);
	void OnWeaponWhipContact(WeaponWhip *whip, ColliderArg e);

	void CheckCollisionToSubWeapon(WeaponBase *weapon);
	void OnSubWeaponContact(WeaponBase *weapon, ColliderArg e);

	void Active();
private:
	//CVGame *cvGame;

};

