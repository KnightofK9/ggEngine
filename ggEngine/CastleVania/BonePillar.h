#pragma once
#include "ShootingEnemyBase.h"
#include "EnemySkillFire.h"
class BonePillar : public ShootingEnemyBase {
public:
	BonePillar(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BonePillar();

	void Update() override;
private:
	void FireLeft(); //Equal fire left
	void FireRight(); //Equal fire right
	void ToggleFireMode();

	int firePauseInterval = 5000;
	int fireSecondInterval = 700;
	const Vector fireLeftPosition = Vector(0, 8);
	const Vector fireRightPosition = Vector(0, 24);

	//const int damage = 2;
	//const int health = 6;
	//const int point = 400;
};