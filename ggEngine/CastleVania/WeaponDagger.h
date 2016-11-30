#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"
using namespace ggEngine;
class WeaponDagger : public WeaponBase {
public:
	WeaponDagger(CVGame *cvGame, SpriteInfo *image);
	~WeaponDagger();

	void FireWeapon(bool isLeft) override;
	void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e) override;
private:

};