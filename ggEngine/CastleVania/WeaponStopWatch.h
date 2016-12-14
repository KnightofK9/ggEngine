#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponStopWatch : public WeaponBase {
public:
	WeaponStopWatch(CVGame *cvGame, SpriteInfo *image);
	virtual ~WeaponStopWatch();

	void FireWeapon(bool isLeft) override;
	int GetHeartConsumtion() override { return this->heartConsumtion; }

private:
	const int heartConsumtion = 5;
	const int duration = 5000;
};