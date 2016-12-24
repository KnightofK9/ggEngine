#pragma once
#include "EnemyBase.h"
#include "EnemySkillFire.h"
class BonePillar : public EnemyBase {
public:
	BonePillar(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BonePillar();

	void Active() override;
	void Update() override;
private:
	void RunLeft() override; //Equal fire left
	void RunRight() override; //Equal fire right
	void Fire(bool isLeft, Vector position);
	EnemySkillFire* AddBullet();

	SpriteInfo* bulletSprite = nullptr;
	const double fireSpeed = 0.25;
	const Vector fireLeftPosition = Vector(0, 8);
	const Vector fireRightPosition = Vector(0, 24);
	const int fireInterval = 1000;
	Timer fireTimer;

	const int damage = 2;
	const int health = 6;
	const int point = 400;
};