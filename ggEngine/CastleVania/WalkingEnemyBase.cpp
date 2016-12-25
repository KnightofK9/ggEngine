#include "WalkingEnemyBase.h"


WalkingEnemyBase::WalkingEnemyBase(CVGame * cvGame, SpriteInfo * spriteInfo,int frameWidth,int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) 
	: EnemyBase(cvGame,spriteInfo, frameWidth, frameHeight, defaultFrame,numberOfFrame,msPerFrame)
{
	
}

WalkingEnemyBase::~WalkingEnemyBase()
{
}

bool WalkingEnemyBase::OnCheckingCollide(ColliderArg e)
{
	auto otherObject = e.colliderObject;
	Tag tag = otherObject->tag;
	switch (tag) {
	case ObjectType_LevelTwoBrick:
		if(this->steppingTile == nullptr) this->steppingTile = dynamic_cast<StaticTile*>(otherObject);
		if (e.blockDirection.down) return true;
		return false;
	default:
		return false;
	}
	return false;
}

void WalkingEnemyBase::RunLeft()
{
	ChangeFacingDirection(true);
	this->body->velocity.x = -moveForce;
}

void WalkingEnemyBase::RunRight()
{
	ChangeFacingDirection(false);
	this->body->velocity.x = moveForce;
}

void WalkingEnemyBase::Update()
{
	EnemyBase::Update();
	if (this->steppingTile != nullptr) {
		if (this->position.x < this->steppingTile->position.x + 8) {
			RunRight();
			return;
		}
		if (this->position.x > this->steppingTile->position.x + this->steppingTile->GetWidth() - 8) {
			RunLeft();
			return;
		}
		if (!this->isRunning) {
			this->isRunning = true;
			RunLeft();
			return;
		}
	}
}

void WalkingEnemyBase::Active()
{
	EnemyBase::Active();
	this->steppingTile = nullptr;
	this->isRunning = false;
}

void WalkingEnemyBase::SetMoveForce(double moveForce)
{
	this->moveForce = moveForce;
}


