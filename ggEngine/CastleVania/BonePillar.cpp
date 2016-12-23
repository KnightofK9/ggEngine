#include "BonePillar.h"
#include "CVGame.h"
#include "TextureConstant.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVMap.h"
BonePillar::BonePillar(CVGame * cvGame, SpriteInfo * spriteInfo) : EnemyBase(cvGame,spriteInfo,16,32)
{
	this->name = "BonePillar";
	this->SetAnchor(0.5, 0);
	this->bulletSprite = this->cvGame->cache->GetSpriteInfo(TextureConstant::SKILL_FIRE_AI_TEXTURE);
	this->body->SetActive(false);
}

BonePillar::~BonePillar()
{
}


void BonePillar::Update()
{
	if (fireTimer.stopwatch(fireInterval)) {
		RunLeft();
		RunRight();
	}
}

void BonePillar::RunLeft()
{
	Fire(true,this->position + this->fireLeftPosition);
}

void BonePillar::RunRight()
{
	Fire(false, this->position + this->fireRightPosition);
}

void BonePillar::Active()
{
	EnemyBase::Active();
	fireTimer.reset();
}

void BonePillar::Fire(bool isLeft, Vector position)
{
	int modifier = 1;
	if (isLeft) modifier = -1;
	auto go = AddBullet();
	this->cvGame->simon->currentMap->projectileGroup->AddDrawObjectToList(go);
	go->SetPosition(position);
	go->UpdateWorldPosition();
	go->body->PreUpdate();
	go->body->velocity.x = modifier*this->fireSpeed;
	go->Active();
}

EnemySkillFire * BonePillar::AddBullet()
{
	EnemySkillFire* go = new EnemySkillFire(this->cvGame, this->bulletSprite);
	return go;
}
