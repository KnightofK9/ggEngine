#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
#include "CVObject.h"
#include "TypeEnum.h"
using namespace ggEngine;
class CVGame;
class EnemyBase;
class Simon;
class WeaponBase : public CVSpriteAnimation, public CVObject {
public:
	WeaponBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 50, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~WeaponBase();

	virtual void FireWeapon(bool isLeft);
	virtual void OnEnemyContact(EnemyBase *enemyBase, ColliderArg e);
	virtual void OnOutOfCamera(EventArg e);
	virtual void OnStaticContact(GameObject *staticObject, ColliderArg e);
	virtual void OnSimonContact(Simon *simon, ColliderArg e);
	virtual void OnBrickContact(GameObject *brick, ColliderArg e);
	virtual void Destroy();

	virtual void Active();
	virtual int GetHeartConsumtion() { return 0; }
	

protected:
	Vector GetHorizontalDirection(bool isLeft);
	Vector GetThrowDirection(bool isLeft);
	virtual void FireHorizontal(bool isLeft, double throwForce);
	virtual void FireAsThrow(bool isLeft, double throwForce);
	CVGame *cvGame;
	//const double throwForce = 1.0;
};