#pragma once
#include "EnemyBase.h"
#include "EnemySkillBase.h"
class ShootingEnemyBase : public EnemyBase {
public:
	ShootingEnemyBase(CVGame *cvGame, SpriteInfo *spriteInfo, int frameWidth, int frameHeight);
	virtual ~ShootingEnemyBase();

	virtual void Active() override;
	virtual void Update() override;
	void SetBullet(EnemySkillBase * bullet);
protected:
	virtual void FireLeft(); 
	virtual void FireRight();

	EnemySkillBase* bullet = nullptr;
	double fireSpeed = 0.25;
	int fireInterval = 1000;
	Timer fireTimer;
};