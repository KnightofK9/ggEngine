#include "Boss3.h"
#include "Simon.h"
#include "Boss3Skill.h"
#include "TextureConstant.h"
#include "CVMap.h"
Boss3::Boss3(CVGame * cvGame, SpriteInfo * image, bool isPrimaryBoss) : WalkingEnemyBase(cvGame,image,16,40,0,3,200)
{
	CreateAnimation("Move", { 0,1,2,1 }, true);
	this->isPrimaryBoss = isPrimaryBoss;
	SetMoveForce(0.25);
	this->allowToDetectSimon = true;
	this->detectY = false;
	fireInterval = 1000;
	this->allowToDetectSimon = false;
	SetBullet(new Boss3Skill(this->cvGame, this->cvGame->cache->GetSpriteInfo(TextureConstant::SKILL_BOSS_3_TEXTURE)));

	this->maxHealth = 16;
	this->damage = 0.5f;
	this->point = 3000;
	this->timeOutToAwake = 1000;
	this->simonDetectRange = 500;
}

Boss3::~Boss3()
{
	if (this->bullet != nullptr) {
		delete this->bullet;
	}
}

void Boss3::Update()
{
	if (!this->isAwake) {
		EnemyBase::Update();
		return;
	}
	WalkingEnemyBase::Update();
	if (fireTimer.stopwatch(fireInterval)) {
		bool isLeft = this->position.x - this->simon->position.x > 0;
		Vector firePosition = this->position;
		firePosition.y += 35;
		Fire(isLeft, firePosition);
	}
}

void Boss3::Active()
{
	WalkingEnemyBase::Active();
	this->isAwake = false;
	this->allowToDetectSimon = true;
}

void Boss3::Fire(bool isLeft, Vector position)
{
	this->bullet->Fire(isLeft, position);
}

void Boss3::SetBullet(EnemySkillBase * bullet)
{
	this->bullet = bullet;
}

void Boss3::Awake()
{
	this->isAwake = true;
	if(this->isPrimaryBoss) this->simon->currentMap->OnEnterBossBlock(this);
}

void Boss3::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	this->allowToDetectSimon = false;
	if (this->awakingTimeOut == nullptr && !this->isAwake) {
		this->awakingTimeOut = this->cvGame->add->TimeOut(this->timeOutToAwake, [=]() {
			Awake();
			this->awakingTimeOut = nullptr;
		})->Start();
	}
}
