#pragma once
#include <ggEngine.h>
#include "CVSprite.h"
#include "TypeEnum.h"
using namespace ggEngine;
class CVGame;
class EnemyBase;
class WeaponBase : public CVSprite {
public:
	WeaponBase(CVGame *cvGame, SpriteInfo *image);
	~WeaponBase();

	virtual void FireWeapon(bool isLeft);
	virtual void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e);
	virtual void OnOutOfCamera(EventArg e);
	virtual void OnStaticContact(GameObject *staticObject, ColliderArg e);

	virtual void Active();

protected:
	CVGame *cvGame;
};