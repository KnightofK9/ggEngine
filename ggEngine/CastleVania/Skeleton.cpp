#include "Skeleton.h"
#include "Simon.h"
Skeleton::Skeleton(CVGame * cvGame, SpriteInfo * image) : ShootingEnemyBase(cvGame,image,16,32,0,2,200)
{
	this->moveSpeed = 0.25;
	this->simonKeepingDistance = 50;
	this->randomFireIntevalMin = 200;
	this->randomFireIntevalMax = 1000;
	this->randomMoveTimeMin = 400;
	this->randomMoveTimeMax = 1200;
	this->randomStopMoveTimeMin = 1000;
	this->randomStopMoveTimeMax = 1200;

	this->CreateAnimation("move", 0, 1, true);
	this->CreateAnimation("idle", 0, 0, false);

	this->body->SetPhysicsMode(PhysicsMode_AABBSwept);
	this->body->allowGravity = true;
	this->body->immoveable = false;
	this->body->SetActive(true);
	this->allowToDetectSimon = false;

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

	this->isPausing = false;
	this->globalModifier = 1;
	this->PlayAnimation("move");
	ResetStoppingTime();
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
		if (isSimonLeft) modifier = 1;
		else modifier = -1;
	}
	if (fireTimer.stopwatch(fireInterval)) {
		fireInterval = Helper::GetRamdomIntNumber(this->randomFireIntevalMin, this->randomFireIntevalMax);	
		if (isSimonLeft) {
			//FireLeft();
		}
		else {
			//FireRight();
		}
	}
	if (this->isMoving) {
		this->body->velocity.x = modifier*this->moveSpeed;
		/*if (!this->isPausing) {
			this->body->velocity.x = modifier*this->moveSpeed;
			this->isMoving = true;
			this->PlayAnimation("move");
		}
		else {
			if (stopTimer.stopwatch(stoppingTimerInterval)) {
				this->isPausing = false;
				this->body->velocity.x = 0;
				ResetStoppingTime();
			}
		}*/
	}
	//else {
	//	if (movingTimer.stopwatch(movingTimerInterval)) {
	//		this->isMoving = false;
	//		this->isPausing = true;
	//		this->PlayAnimation("idle");
	//		ResetMovingTime();
	//	}
	//}
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

void Skeleton::ResetStoppingTime()
{
	this->stoppingTimerInterval = Helper::GetRamdomIntNumber(this->randomStopMoveTimeMin, this->randomStopMoveTimeMax);

}

void Skeleton::ResetMovingTime()
{
	this->movingTimerInterval = Helper::GetRamdomIntNumber(this->randomMoveTimeMin, this->randomMoveTimeMax);

}
