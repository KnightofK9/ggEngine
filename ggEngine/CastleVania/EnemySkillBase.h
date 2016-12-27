#pragma once
#include "CVSpriteAnimation.h"
class EnemyBase;
class EnemySkillBase : public CVSpriteAnimation {
public:
	EnemySkillBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemySkillBase();

	virtual void Active();
	void SetParentObject(EnemyBase *enemyBase);
	virtual void Fire(bool isLeft, Vector position);
	virtual void ChangeFacingDirection(bool isLeft);
	virtual double GetDamage() { return damage; }

protected:
	void AddBulletToGroup(EnemySkillBase * bullet);
	virtual EnemySkillBase * GetBulletInstance();
	virtual void OnSimonContact(ColliderArg e);
	virtual bool OnCheckingCollide(ColliderArg e);
	EnemyBase *enemyBase;
	bool isLeft;
	double fireSpeed = 0.25;
	double damage;
};


