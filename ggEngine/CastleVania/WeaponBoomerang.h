#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponBoomerang : public WeaponBase {
public:
	WeaponBoomerang(CVGame *cvGame, SpriteInfo *image);
	virtual ~WeaponBoomerang();

	void FireWeapon(bool isLeft) override;
	void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e) override;

	const int heartConsumtion = 1;

private:
	const double throwForce = 1.0;
	const int timeToReturn = 1300;
	bool isLeft;
	bool contactedWorldBound = false;
};