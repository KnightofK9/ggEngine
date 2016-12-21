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
	void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e) override;
	void OnSimonContact(Simon *simon, ColliderArg e);
	int GetHeartConsumtion() override { return this->heartConsumtion; }

private:
	const int heartConsumtion = 1;
	const double throwForce = 1.0;
	const int timeToReturn = 1300;
	const int distanceToReturn = 100;
	int distanceCal = distanceToReturn;
	bool isLeft;
	bool contactedWorldBound = false;
};