#pragma once
#include "EnemyBase.h"
#include "EnemySkillBase.h"
class ShootingEnemyBase : public EnemyBase {
public:
	ShootingEnemyBase(CVGame *cvGame, SpriteInfo *spriteInfo, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~ShootingEnemyBase();

	virtual void Active() override;
	virtual void Update() override;
	void SetBullet(EnemySkillBase * bullet);
protected:
	virtual void FireLeft(); 
	virtual void FireRight();

	EnemySkillBase* bullet = nullptr;
	int fireInterval = 1000;
	Timer fireTimer;
};