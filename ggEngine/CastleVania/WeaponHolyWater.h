#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponHolyWater : public WeaponBase {
public:
	WeaponHolyWater(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);;
	virtual ~WeaponHolyWater();

	void FireWeapon(bool isLeft) override;
	int GetHeartConsumtion() override { return this->heartConsumtion; }
	
	void OnBrickContact(GameObject *go, ColliderArg e) override;

private:
	const int heartConsumtion = 1;
	const double throwForce = 2;
};