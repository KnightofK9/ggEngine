#pragma once
#include "ShootingEnemyBase.h"
#include "EnemySkillFire.h"
class BonePillar : public ShootingEnemyBase {
public:
	BonePillar(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BonePillar();

private:
	void FireLeft(); //Equal fire left
	void FireRight(); //Equal fire right

	const Vector fireLeftPosition = Vector(0, 8);
	const Vector fireRightPosition = Vector(0, 24);
};