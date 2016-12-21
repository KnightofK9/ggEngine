#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponStopWatch : public WeaponBase {
public:
	WeaponStopWatch(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~WeaponStopWatch();

	void FireWeapon(bool isLeft) override;
	int GetHeartConsumtion() override { return this->heartConsumtion; }

private:
	const int heartConsumtion = 5;
	const int duration = 5000;
};