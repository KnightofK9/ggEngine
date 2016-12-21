#pragma once
#include <ggEngine.h>
#include "DropObjectBase.h"

using namespace ggEngine;
class CVGame;
class WeaponWhip;
class WeaponBase;
class Candle : public DropObjectBase
{
public:
	Candle(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~Candle();

	void OnWeaponWhipContact(WeaponWhip *whip, ColliderArg e) override;
	void OnSubWeaponContact(WeaponBase *weapon, ColliderArg e) override;
	void Active() override;
private:
	//CVGame *cvGame;

};

