#include "Boss3.h"
#include "Simon.h"
#include "Boss3Skill.h"
#include "TextureConstant.h"
Boss3::Boss3(CVGame * cvGame, SpriteInfo * image, bool isPrimaryBoss) : WalkingEnemyBase(cvGame,image,16,40,0,3,200)
{
	CreateAnimation("Move", { 0,1,2,1 }, true);
	this->isPrimaryBoss = isPrimaryBoss;
	SetMoveForce(0.25);
	this->allowToDetectSimon = true;
	this->detectY = false;
	fireInterval = 1000;
	this->allowToDetectSimon = true;
	SetBullet(new Boss3Skill(this->cvGame, this->cvGame->cache->GetSpriteInfo(TextureConstant::BOSS_3_TEXTURE)));
}

Boss3::~Boss3()
{
	if (this->bullet != nullptr) {
		delete this->bullet;
	}
}

void Boss3::Update()
{
	WalkingEnemyBase::Update();
	if (fireTimer.stopwatch(fireInterval)) {
		bool isLeft = this->position.x - this->simon->position.x > 0;
		Fire(isLeft, this->position);
	}
}

void Boss3::Fire(bool isLeft, Vector position)
{
	this->bullet->Fire(isLeft, position);
}

void Boss3::SetBullet(EnemySkillBase * bullet)
{
	this->bullet = bullet;
}
