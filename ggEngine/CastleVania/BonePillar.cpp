#include "BonePillar.h"
#include "CVGame.h"
#include "TextureConstant.h"
BonePillar::BonePillar(CVGame * cvGame, SpriteInfo * spriteInfo) 
	: ShootingEnemyBase(cvGame,spriteInfo,16,32)
{
	this->name = "BonePillar";
	this->SetAnchor(0.5, 0);
	this->SetBullet(new EnemySkillFire(this->cvGame, 
		this->cvGame->cache->GetSpriteInfo(TextureConstant::SKILL_FIRE_AI_TEXTURE)));
	this->body->SetActive(false);

	this->fireInterval = firePauseInterval;
	this->maxHealth = 6;
	this->damage = 2;
	this->point = 400;
}

BonePillar::~BonePillar()
{
}

void BonePillar::Update()
{
	EnemyBase::Update();
	if (fireTimer.stopwatch(fireInterval)) {
		FireLeft();
		FireRight();
		ToggleFireMode();
	}
}



void BonePillar::FireLeft()
{
	this->bullet->Fire(true, this->position + this->fireLeftPosition);
}

void BonePillar::FireRight()
{
	this->bullet->Fire(false, this->position + this->fireRightPosition);
}

void BonePillar::ToggleFireMode()
{
	if (this->fireInterval == firePauseInterval) {
		fireInterval = fireSecondInterval;
	}
	else {
		fireInterval = firePauseInterval;
	}
}

