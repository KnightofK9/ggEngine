#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
#include "Simon.h"
using namespace ggEngine;
class WeaponBoomerang : public WeaponBase {
public:
	WeaponBoomerang(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~WeaponBoomerang();

	void FireWeapon(bool isLeft) override;
	void OnSimonContact(ColliderArg e) override;
	void OnOutOfCamera(EventArg e) override;
	int GetHeartConsumtion() override { return this->heartConsumtion; }

	void SetPreparerForReturn(std::function<void()> preReturn);

private:
	const int heartConsumtion = 1;
	const double throwForce = 1.0;
	const int timeToReturn = 1300;
	const int distanceToReturn = 100;
	bool isLeft;
	bool contactedWorldBound = false;

	TweenBase *tweenOut = nullptr;
	TweenBase *tweenReturn = nullptr;

	std::function<void()> preReturn;
};