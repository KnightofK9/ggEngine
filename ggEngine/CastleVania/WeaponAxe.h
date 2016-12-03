#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponAxe : public WeaponBase {
public:
	WeaponAxe(CVGame *cvGame, SpriteInfo *image);
	virtual ~WeaponAxe();

	void FireWeapon(bool isLeft) override;
	void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e) override;

	const int heartConsumtion = 1;

private:
	const double throwForce = 3;
};

