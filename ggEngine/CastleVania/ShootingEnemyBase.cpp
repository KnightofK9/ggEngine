#include "ShootingEnemyBase.h"

ShootingEnemyBase::ShootingEnemyBase(CVGame * cvGame, SpriteInfo * spriteInfo, int frameWidth, int frameHeight) 
	: EnemyBase(cvGame,spriteInfo,frameWidth,frameHeight)
{

}

ShootingEnemyBase::~ShootingEnemyBase()
{
	delete this->bullet;
}

void ShootingEnemyBase::Active()
{
	EnemyBase::Active();
	fireTimer.reset();
}

void ShootingEnemyBase::Update()
{
	EnemyBase::Update();
	if (fireTimer.stopwatch(fireInterval)) {
		FireLeft();
		FireRight();
	}
}

void ShootingEnemyBase::SetBullet(EnemySkillBase * bullet)
{
	this->bullet = bullet;
}

void ShootingEnemyBase::FireLeft()
{
	this->bullet->Fire(true, this->position);
}

void ShootingEnemyBase::FireRight()
{
	this->bullet->Fire(false, this->position);
}

