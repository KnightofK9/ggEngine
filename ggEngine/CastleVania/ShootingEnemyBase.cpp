#include "ShootingEnemyBase.h"

ShootingEnemyBase::ShootingEnemyBase(CVGame * cvGame, SpriteInfo * spriteInfo, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: EnemyBase(cvGame,spriteInfo,frameWidth,frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	fireInterval = 1000;
	this->body->SetPhysicsMode(PhysicsMode_AABB);
}

ShootingEnemyBase::~ShootingEnemyBase()
{
	if (this->bullet != nullptr) {
		delete this->bullet;
	}
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


