#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponHolyWater : public WeaponBase {
public:
	WeaponHolyWater(CVGame *cvGame, SpriteInfo *image);
	virtual ~WeaponHolyWater();

	void FireWeapon(bool isLeft) override;
	void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e) override;
	int GetHeartConsumtion() override { return this->heartConsumtion; }


private:
	const int heartConsumtion = 1;
	const double throwForce = 1.0;
};