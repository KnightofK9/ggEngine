#include "Skeleton.h"
#include "Simon.h"
#include "TileBrick.h"
#include "SkeletonSkill.h"
#include "TextureConstant.h"
Skeleton::Skeleton(CVGame * cvGame, SpriteInfo * image)
	: ShootingEnemyBase(cvGame,image,16,32,0,2,200)
{
	this->moveSpeed = 0.25;
	this->jumpForce = 3;
	this->simonKeepingDistance = 50;
	this->randomFireIntevalMin = 200;
	this->randomFireIntevalMax = 1000;
	this->randomMoveTimeMin = 1200;
	this->randomMoveTimeMax = 2000;

	this->CreateAnimation("move", 0, 1, true);
	this->CreateAnimation("idle", 0, 0, false);

	this->body->SetPhysicsMode(PhysicsMode_AABBSwept);
	this->body->allowGravity = true;
	this->body->immoveable = false;
	this->body->SetActive(true);
	this->allowToDetectSimon = false;
	SetBullet(new SkeletonSkill(this->cvGame, this->cvGame->cache->GetSpriteInfo(TextureConstant::SKILL_AI_TEXTURE)));

	this->maxHealth = 1;
	this->damage = 3;
	this->point = 300;
}

Skeleton::~Skeleton()
{
}

void Skeleton::Active()
{
	ShootingEnemyBase::Active();
	this->movingTimer.reset();
	this->stopTimer.reset();
	this->isMoving = true;

	this->globalModifier = 1;
	this->PlayAnimation("move");
	ResetMovingTime();
}

void Skeleton::Update()
{
	EnemyBase::Update();
	double distance = this->position.x - this->simon->position.x;
	bool isSimonLeft = distance > 0;
	int modifier = 1;
	if (isSimonLeft) modifier = -1;
	if (movingTimer.stopwatch(movingTimerInterval)) {
		globalModifier *= -1;
		ResetMovingTime();
	}
	modifier *= globalModifier;
	this->ChangeFacingDirection(isSimonLeft);
	if (abs(distance) < this->simonKeepingDistance) {
		movingTimerInterval = 0;
		if (isSimonLeft) modifier = 1;
		else modifier = -1;
	}
	else {
		movingTimerInterval += Helper::GetRamdomIntNumber(-5, 10);
	}
	if (fireTimer.stopwatch(fireInterval)) {
		fireInterval = Helper::GetRamdomIntNumber(this->randomFireIntevalMin, this->randomFireIntevalMax);	
		if (isSimonLeft) {
			FireLeft();
		}
		else {
			FireRight();
		}
	}
	if (this->isMoving) {
		this->body->velocity.x = modifier*this->moveSpeed;
	}
}

void Skeleton::OnBrickContact(TileBrick * tileBrick, ColliderArg e)
{
	if (e.blockDirection.down) {
		if (tileBrick->IsOnEdge(this)) {
			bool isLeft = this->body->velocity.x < 0;
			int modifier = 1;
			if (isLeft) modifier = -1;
			this->body->SetForce(this->jumpForce, Vector(modifier/2.0, -1));
			//this->body->velocity.y = -this->jumpForce;
		}
	}
}

bool Skeleton::OnCheckingCollide(ColliderArg e)
{
	Tag tag = e.colliderObject->tag;
	switch (tag) {
	case ObjectType_LevelTwoBrick:
	case ObjectType_BreakableTileBrick:
		if (e.blockDirection.up) return false;
		if (e.blockDirection.left) {
			this->body->velocity.x = abs(this->body->velocity.x);
		}
		if (e.blockDirection.right) {
			this->body->velocity.x = -abs(this->body->velocity.x);
		}
		return true;
	default:
		break;
	}
	return false;
}

void Skeleton::OnSimonEnterRange(Simon * simon, bool isLeft)
{
}

void Skeleton::ResetMovingTime()
{
	this->movingTimerInterval = Helper::GetRamdomIntNumber(this->randomMoveTimeMin, this->randomMoveTimeMax);

}
